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
typedef  scalar_t__ vm_paddr_t ;

/* Variables and functions */
 int nitems (scalar_t__*) ; 
 scalar_t__* xlp_mem_excl ; 

__attribute__((used)) static int
mem_exclude_add(vm_paddr_t *avail, vm_paddr_t mstart, vm_paddr_t mend)
{
	int i, pos;

	pos = 0;
	for (i = 0; i < nitems(xlp_mem_excl); i += 2) {
		if (mstart > xlp_mem_excl[i + 1])
			continue;
		if (mstart < xlp_mem_excl[i]) {
			avail[pos++] = mstart;
			if (mend < xlp_mem_excl[i])
				avail[pos++] = mend;
			else
				avail[pos++] = xlp_mem_excl[i];
		}
		mstart = xlp_mem_excl[i + 1];
		if (mend <= mstart)
			break;
	}
	if (mstart < mend) {
		avail[pos++] = mstart;
		avail[pos++] = mend;
	}
	return (pos);
}