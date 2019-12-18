#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u32 ;
struct microcode_header_intel {int ldrver; int hdrver; size_t sig; size_t pf; size_t cksum; } ;
struct extended_sigtable {size_t count; } ;
struct extended_signature {size_t sig; size_t pf; size_t cksum; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 unsigned long EXT_HEADER_SIZE ; 
 unsigned long EXT_SIGNATURE_SIZE ; 
 unsigned long MC_HEADER_SIZE ; 
 unsigned long exttable_size (struct extended_sigtable*) ; 
 unsigned long get_datasize (struct microcode_header_intel*) ; 
 unsigned long get_totalsize (struct microcode_header_intel*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int microcode_sanity_check(void *mc, int print_err)
{
	unsigned long total_size, data_size, ext_table_size;
	struct microcode_header_intel *mc_header = mc;
	struct extended_sigtable *ext_header = NULL;
	u32 sum, orig_sum, ext_sigcount = 0, i;
	struct extended_signature *ext_sig;

	total_size = get_totalsize(mc_header);
	data_size = get_datasize(mc_header);

	if (data_size + MC_HEADER_SIZE > total_size) {
		if (print_err)
			pr_err("Error: bad microcode data file size.\n");
		return -EINVAL;
	}

	if (mc_header->ldrver != 1 || mc_header->hdrver != 1) {
		if (print_err)
			pr_err("Error: invalid/unknown microcode update format.\n");
		return -EINVAL;
	}

	ext_table_size = total_size - (MC_HEADER_SIZE + data_size);
	if (ext_table_size) {
		u32 ext_table_sum = 0;
		u32 *ext_tablep;

		if ((ext_table_size < EXT_HEADER_SIZE)
		 || ((ext_table_size - EXT_HEADER_SIZE) % EXT_SIGNATURE_SIZE)) {
			if (print_err)
				pr_err("Error: truncated extended signature table.\n");
			return -EINVAL;
		}

		ext_header = mc + MC_HEADER_SIZE + data_size;
		if (ext_table_size != exttable_size(ext_header)) {
			if (print_err)
				pr_err("Error: extended signature table size mismatch.\n");
			return -EFAULT;
		}

		ext_sigcount = ext_header->count;

		/*
		 * Check extended table checksum: the sum of all dwords that
		 * comprise a valid table must be 0.
		 */
		ext_tablep = (u32 *)ext_header;

		i = ext_table_size / sizeof(u32);
		while (i--)
			ext_table_sum += ext_tablep[i];

		if (ext_table_sum) {
			if (print_err)
				pr_warn("Bad extended signature table checksum, aborting.\n");
			return -EINVAL;
		}
	}

	/*
	 * Calculate the checksum of update data and header. The checksum of
	 * valid update data and header including the extended signature table
	 * must be 0.
	 */
	orig_sum = 0;
	i = (MC_HEADER_SIZE + data_size) / sizeof(u32);
	while (i--)
		orig_sum += ((u32 *)mc)[i];

	if (orig_sum) {
		if (print_err)
			pr_err("Bad microcode data checksum, aborting.\n");
		return -EINVAL;
	}

	if (!ext_table_size)
		return 0;

	/*
	 * Check extended signature checksum: 0 => valid.
	 */
	for (i = 0; i < ext_sigcount; i++) {
		ext_sig = (void *)ext_header + EXT_HEADER_SIZE +
			  EXT_SIGNATURE_SIZE * i;

		sum = (mc_header->sig + mc_header->pf + mc_header->cksum) -
		      (ext_sig->sig + ext_sig->pf + ext_sig->cksum);
		if (sum) {
			if (print_err)
				pr_err("Bad extended signature checksum, aborting.\n");
			return -EINVAL;
		}
	}
	return 0;
}