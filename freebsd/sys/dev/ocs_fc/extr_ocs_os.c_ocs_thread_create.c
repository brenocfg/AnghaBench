#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int /*<<< orphan*/  tcb; int /*<<< orphan*/  terminate; void* arg; int /*<<< orphan*/  fctn; } ;
typedef  TYPE_1__ ocs_thread_t ;
typedef  scalar_t__ ocs_thread_start_e ;
typedef  int /*<<< orphan*/  ocs_thread_fctn ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ OCS_THREAD_CREATE ; 
 int /*<<< orphan*/  OCS_THREAD_DEFAULT_STACK_SIZE_PAGES ; 
 int /*<<< orphan*/  RFSTOPPED ; 
 int /*<<< orphan*/  kthread_add (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ocs_atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* ocs_strdup (char const*) ; 
 int /*<<< orphan*/  ocs_thread_call_fctn ; 

int32_t
ocs_thread_create(ocs_os_handle_t os, ocs_thread_t *thread, ocs_thread_fctn fctn, const char *name, void *arg, ocs_thread_start_e start)
{
	int32_t rc = 0;

	ocs_memset(thread, 0, sizeof(*thread));

	thread->fctn = fctn;
	thread->name = ocs_strdup(name);
	if (thread->name == NULL) {
		thread->name = "unknown";
	}
	thread->arg = arg;

	ocs_atomic_set(&thread->terminate, 0);

	rc = kthread_add(ocs_thread_call_fctn, thread, NULL, &thread->tcb, (start == OCS_THREAD_CREATE) ? RFSTOPPED : 0,
		OCS_THREAD_DEFAULT_STACK_SIZE_PAGES, "%s", name);

	return rc;
}