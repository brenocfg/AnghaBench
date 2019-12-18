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
typedef  int u64 ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int fls64 (int) ; 
 long min (long,long) ; 
 scalar_t__ unlikely (char const**) ; 
 char** xfeature_names ; 
 int xfeatures_mask ; 

int cpu_has_xfeatures(u64 xfeatures_needed, const char **feature_name)
{
	u64 xfeatures_missing = xfeatures_needed & ~xfeatures_mask;

	if (unlikely(feature_name)) {
		long xfeature_idx, max_idx;
		u64 xfeatures_print;
		/*
		 * So we use FLS here to be able to print the most advanced
		 * feature that was requested but is missing. So if a driver
		 * asks about "XFEATURE_MASK_SSE | XFEATURE_MASK_YMM" we'll print the
		 * missing AVX feature - this is the most informative message
		 * to users:
		 */
		if (xfeatures_missing)
			xfeatures_print = xfeatures_missing;
		else
			xfeatures_print = xfeatures_needed;

		xfeature_idx = fls64(xfeatures_print)-1;
		max_idx = ARRAY_SIZE(xfeature_names)-1;
		xfeature_idx = min(xfeature_idx, max_idx);

		*feature_name = xfeature_names[xfeature_idx];
	}

	if (xfeatures_missing)
		return 0;

	return 1;
}