#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_3__ {void* dtpr_arg; int /*<<< orphan*/ * dtpr_provider; } ;
typedef  TYPE_1__ dtrace_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_lock ; 
 TYPE_1__* dtrace_probe_lookup_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void *
dtrace_probe_arg(dtrace_provider_id_t id, dtrace_id_t pid)
{
	dtrace_probe_t *probe;
	void *rval = NULL;

	mutex_enter(&dtrace_lock);

	if ((probe = dtrace_probe_lookup_id(pid)) != NULL &&
	    probe->dtpr_provider == (dtrace_provider_t *)id)
		rval = probe->dtpr_arg;

	mutex_exit(&dtrace_lock);

	return (rval);
}