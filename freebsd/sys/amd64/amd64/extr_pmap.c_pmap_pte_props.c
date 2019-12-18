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
typedef  int u_long ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fcmpset_long (int*,int*,int) ; 

__attribute__((used)) static __inline void
pmap_pte_props(pt_entry_t *pte, u_long bits, u_long mask)
{
	u_long opte, npte;

	opte = *(u_long *)pte;
	do {
		npte = opte & ~mask;
		npte |= bits;
	} while (npte != opte && !atomic_fcmpset_long((u_long *)pte, &opte,
	    npte));
}