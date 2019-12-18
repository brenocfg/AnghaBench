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
typedef  int pid_t ;
struct TYPE_4__ {scalar_t__ td_tid; TYPE_1__* td_proc; } ;
struct TYPE_3__ {int p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,int,long) ; 
 TYPE_2__* kdb_thread ; 

void
db_print_thread(void)
{
	pid_t pid;

	pid = -1;
	if (kdb_thread->td_proc != NULL)
		pid = kdb_thread->td_proc->p_pid;
	db_printf("[ thread pid %d tid %ld ]\n", pid, (long)kdb_thread->td_tid);
}