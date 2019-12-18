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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 
 unsigned long sun4u_huge_tte_to_shift (int /*<<< orphan*/ ) ; 
 unsigned long sun4v_huge_tte_to_shift (int /*<<< orphan*/ ) ; 
 scalar_t__ tlb_type ; 

__attribute__((used)) static unsigned int huge_tte_to_shift(pte_t entry)
{
	unsigned long shift;

	if (tlb_type == hypervisor)
		shift = sun4v_huge_tte_to_shift(entry);
	else
		shift = sun4u_huge_tte_to_shift(entry);

	if (shift == PAGE_SHIFT)
		WARN_ONCE(1, "tto_to_shift: invalid hugepage tte=0x%lx\n",
			  pte_val(entry));

	return shift;
}