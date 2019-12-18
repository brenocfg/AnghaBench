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
typedef  int /*<<< orphan*/  pud_t ;

/* Variables and functions */
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  pudp_flush_direct (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 

pud_t pudp_xchg_direct(struct mm_struct *mm, unsigned long addr,
		       pud_t *pudp, pud_t new)
{
	pud_t old;

	preempt_disable();
	old = pudp_flush_direct(mm, addr, pudp);
	*pudp = new;
	preempt_enable();
	return old;
}