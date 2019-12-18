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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmdp_flush_direct (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

pmd_t pmdp_xchg_direct(struct mm_struct *mm, unsigned long addr,
		       pmd_t *pmdp, pmd_t new)
{
	pmd_t old;

	preempt_disable();
	old = pmdp_flush_direct(mm, addr, pmdp);
	*pmdp = new;
	preempt_enable();
	return old;
}