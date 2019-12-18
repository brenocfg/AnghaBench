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

/* Variables and functions */
 int PERF_BR_UNKNOWN ; 
 int X86_BR_TYPE_MAP_MAX ; 
 int __ffs (int) ; 
 int* branch_map ; 

__attribute__((used)) static int
common_branch_type(int type)
{
	int i;

	type >>= 2; /* skip X86_BR_USER and X86_BR_KERNEL */

	if (type) {
		i = __ffs(type);
		if (i < X86_BR_TYPE_MAP_MAX)
			return branch_map[i];
	}

	return PERF_BR_UNKNOWN;
}