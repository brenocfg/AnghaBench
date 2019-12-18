#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ processor_rev_id; } ;
struct microcode_amd {TYPE_1__ hdr; } ;
struct equiv_cpu_table {int num_entries; struct equiv_cpu_entry* entry; } ;
struct equiv_cpu_entry {int dummy; } ;
struct cont_desc {int psize; size_t size; int /*<<< orphan*/ * data; struct microcode_amd* mc; int /*<<< orphan*/  cpuid_1_eax; } ;

/* Variables and functions */
 int CONTAINER_HDR_SZ ; 
 int SECTION_HDR_SIZE ; 
 scalar_t__ find_equiv_id (struct equiv_cpu_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_equivalence_table (int /*<<< orphan*/ *,size_t,int) ; 
 int verify_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int*,int) ; 
 int /*<<< orphan*/  x86_family (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t parse_container(u8 *ucode, size_t size, struct cont_desc *desc)
{
	struct equiv_cpu_table table;
	size_t orig_size = size;
	u32 *hdr = (u32 *)ucode;
	u16 eq_id;
	u8 *buf;

	if (!verify_equivalence_table(ucode, size, true))
		return 0;

	buf = ucode;

	table.entry = (struct equiv_cpu_entry *)(buf + CONTAINER_HDR_SZ);
	table.num_entries = hdr[2] / sizeof(struct equiv_cpu_entry);

	/*
	 * Find the equivalence ID of our CPU in this table. Even if this table
	 * doesn't contain a patch for the CPU, scan through the whole container
	 * so that it can be skipped in case there are other containers appended.
	 */
	eq_id = find_equiv_id(&table, desc->cpuid_1_eax);

	buf  += hdr[2] + CONTAINER_HDR_SZ;
	size -= hdr[2] + CONTAINER_HDR_SZ;

	/*
	 * Scan through the rest of the container to find where it ends. We do
	 * some basic sanity-checking too.
	 */
	while (size > 0) {
		struct microcode_amd *mc;
		u32 patch_size;
		int ret;

		ret = verify_patch(x86_family(desc->cpuid_1_eax), buf, size, &patch_size, true);
		if (ret < 0) {
			/*
			 * Patch verification failed, skip to the next
			 * container, if there's one:
			 */
			goto out;
		} else if (ret > 0) {
			goto skip;
		}

		mc = (struct microcode_amd *)(buf + SECTION_HDR_SIZE);
		if (eq_id == mc->hdr.processor_rev_id) {
			desc->psize = patch_size;
			desc->mc = mc;
		}

skip:
		/* Skip patch section header too: */
		buf  += patch_size + SECTION_HDR_SIZE;
		size -= patch_size + SECTION_HDR_SIZE;
	}

	/*
	 * If we have found a patch (desc->mc), it means we're looking at the
	 * container which has a patch for this CPU so return 0 to mean, @ucode
	 * already points to the proper container. Otherwise, we return the size
	 * we scanned so that we can advance to the next container in the
	 * buffer.
	 */
	if (desc->mc) {
		desc->data = ucode;
		desc->size = orig_size - size;

		return 0;
	}

out:
	return orig_size - size;
}