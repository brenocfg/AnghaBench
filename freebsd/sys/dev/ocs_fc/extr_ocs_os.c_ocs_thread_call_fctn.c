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
struct TYPE_2__ {scalar_t__ name; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* fctn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  retval; } ;
typedef  TYPE_1__ ocs_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_strlen (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_thread_call_fctn(void *arg)
{
	ocs_thread_t *thread = arg;
	thread->retval = (*thread->fctn)(thread->arg);
	ocs_free(NULL, thread->name, ocs_strlen(thread->name+1));
	kthread_exit();
}