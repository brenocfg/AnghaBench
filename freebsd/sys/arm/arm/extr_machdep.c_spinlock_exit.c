#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ md_spinlock_count; int /*<<< orphan*/  md_saved_cspr; } ;
struct thread {TYPE_1__ td_md; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  restore_interrupts (int /*<<< orphan*/ ) ; 

void
spinlock_exit(void)
{
	struct thread *td;
	register_t cspr;

	td = curthread;
	critical_exit();
	cspr = td->td_md.md_saved_cspr;
	td->td_md.md_spinlock_count--;
	if (td->td_md.md_spinlock_count == 0)
		restore_interrupts(cspr);
}