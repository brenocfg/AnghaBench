#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_2__* td_proc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * md_ldt; } ;
struct TYPE_4__ {TYPE_1__ p_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  user_ldt_free (struct thread*) ; 

void
cpu_exit(struct thread *td)
{

	/*
	 * If this process has a custom LDT, release it.
	 */
	if (td->td_proc->p_md.md_ldt != NULL)
		user_ldt_free(td);
}