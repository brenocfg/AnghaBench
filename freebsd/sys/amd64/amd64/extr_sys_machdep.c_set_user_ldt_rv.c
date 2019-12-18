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
struct vmspace {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_md; struct vmspace* p_vmspace; } ;

/* Variables and functions */
 struct thread* curthread ; 
 int /*<<< orphan*/  set_user_ldt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_user_ldt_rv(struct vmspace *vmsp)
{
	struct thread *td;

	td = curthread;
	if (vmsp != td->td_proc->p_vmspace)
		return;

	set_user_ldt(&td->td_proc->p_md);
}