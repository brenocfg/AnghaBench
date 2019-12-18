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
struct vm_area_struct {int dummy; } ;
struct spinlock {int dummy; } ;

/* Variables and functions */
 scalar_t__ radix_enabled () ; 
 scalar_t__ vma_is_anonymous (struct vm_area_struct*) ; 

int pmd_move_must_withdraw(struct spinlock *new_pmd_ptl,
			   struct spinlock *old_pmd_ptl,
			   struct vm_area_struct *vma)
{
	if (radix_enabled())
		return (new_pmd_ptl != old_pmd_ptl) && vma_is_anonymous(vma);

	return true;
}