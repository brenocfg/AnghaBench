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
struct TYPE_2__ {int md_spinlock_count; int /*<<< orphan*/  md_saved_cspr; } ;
struct thread {TYPE_1__ td_md; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int PSR_F ; 
 int PSR_I ; 
 int /*<<< orphan*/  critical_enter () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  disable_interrupts (int) ; 

void
spinlock_enter(void)
{
	struct thread *td;
	register_t cspr;

	td = curthread;
	if (td->td_md.md_spinlock_count == 0) {
		cspr = disable_interrupts(PSR_I | PSR_F);
		td->td_md.md_spinlock_count = 1;
		td->td_md.md_saved_cspr = cspr;
	} else
		td->td_md.md_spinlock_count++;
	critical_enter();
}