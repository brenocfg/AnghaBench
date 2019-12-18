#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  regs; } ;
struct TYPE_8__ {int (* proc ) (void*) ;void* arg; } ;
struct TYPE_9__ {TYPE_1__ thread; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_12__ {TYPE_4__ regs; TYPE_3__ request; int /*<<< orphan*/ * prev_sched; } ;
struct TYPE_14__ {TYPE_5__ thread; } ;
struct TYPE_13__ {int /*<<< orphan*/  aux_fp_regs; } ;

/* Variables and functions */
 TYPE_7__* current ; 
 TYPE_6__* current_thread_info () ; 
 int /*<<< orphan*/  schedule_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void new_thread_handler(void)
{
	int (*fn)(void *), n;
	void *arg;

	if (current->thread.prev_sched != NULL)
		schedule_tail(current->thread.prev_sched);
	current->thread.prev_sched = NULL;

	fn = current->thread.request.u.thread.proc;
	arg = current->thread.request.u.thread.arg;

	/*
	 * callback returns only if the kernel thread execs a process
	 */
	n = fn(arg);
	userspace(&current->thread.regs.regs, current_thread_info()->aux_fp_regs);
}