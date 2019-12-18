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
struct gcov_info {int version; int stamp; unsigned int n_functions; struct gcov_fn_info** functions; } ;
struct gcov_fn_info {int ident; int lineno_checksum; int cfg_checksum; struct gcov_ctr_info* ctrs; } ;
struct gcov_ctr_info {int num; int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 unsigned int GCOV_COUNTERS ; 
 int GCOV_DATA_MAGIC ; 
 int GCOV_TAG_FOR_COUNTER (unsigned int) ; 
 int GCOV_TAG_FUNCTION ; 
 int GCOV_TAG_FUNCTION_LENGTH ; 
 int /*<<< orphan*/  counter_active (struct gcov_info*,unsigned int) ; 
 scalar_t__ store_gcov_uint32 (char*,size_t,int) ; 
 scalar_t__ store_gcov_uint64 (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
convert_to_gcda(char *buffer, struct gcov_info *info)
{
	struct gcov_fn_info *fi_ptr;
	struct gcov_ctr_info *ci_ptr;
	unsigned int fi_idx;
	unsigned int ct_idx;
	unsigned int cv_idx;
	size_t pos = 0;

	/* File header. */
	pos += store_gcov_uint32(buffer, pos, GCOV_DATA_MAGIC);
	pos += store_gcov_uint32(buffer, pos, info->version);
	pos += store_gcov_uint32(buffer, pos, info->stamp);

	for (fi_idx = 0; fi_idx < info->n_functions; fi_idx++) {
		fi_ptr = info->functions[fi_idx];

		/* Function record. */
		pos += store_gcov_uint32(buffer, pos, GCOV_TAG_FUNCTION);
		pos += store_gcov_uint32(buffer, pos, GCOV_TAG_FUNCTION_LENGTH);
		pos += store_gcov_uint32(buffer, pos, fi_ptr->ident);
		pos += store_gcov_uint32(buffer, pos, fi_ptr->lineno_checksum);
		pos += store_gcov_uint32(buffer, pos, fi_ptr->cfg_checksum);

		ci_ptr = fi_ptr->ctrs;

		for (ct_idx = 0; ct_idx < GCOV_COUNTERS; ct_idx++) {
			if (!counter_active(info, ct_idx))
				continue;

			/* Counter record. */
			pos += store_gcov_uint32(buffer, pos,
					      GCOV_TAG_FOR_COUNTER(ct_idx));
			pos += store_gcov_uint32(buffer, pos, ci_ptr->num * 2);

			for (cv_idx = 0; cv_idx < ci_ptr->num; cv_idx++) {
				pos += store_gcov_uint64(buffer, pos,
						      ci_ptr->values[cv_idx]);
			}

			ci_ptr++;
		}
	}

	return (pos);
}