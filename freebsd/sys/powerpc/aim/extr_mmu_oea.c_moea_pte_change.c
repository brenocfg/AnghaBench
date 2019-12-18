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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct pte {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  moea_pte_set (struct pte*,struct pte*) ; 
 int /*<<< orphan*/  moea_pte_unset (struct pte*,struct pte*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
moea_pte_change(struct pte *pt, struct pte *pvo_pt, vm_offset_t va)
{

	/*
	 * Invalidate the PTE
	 */
	moea_pte_unset(pt, pvo_pt, va);
	moea_pte_set(pt, pvo_pt);
}