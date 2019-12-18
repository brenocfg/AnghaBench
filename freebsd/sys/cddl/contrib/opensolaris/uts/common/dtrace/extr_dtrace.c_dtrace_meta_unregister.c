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
struct TYPE_5__ {scalar_t__ dtm_count; struct TYPE_5__* dtm_name; } ;
typedef  TYPE_1__ dtrace_meta_t ;
typedef  scalar_t__ dtrace_meta_provider_id_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 TYPE_1__* dtrace_meta_pid ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 int strlen (TYPE_1__*) ; 

int
dtrace_meta_unregister(dtrace_meta_provider_id_t id)
{
	dtrace_meta_t **pp, *old = (dtrace_meta_t *)id;

	mutex_enter(&dtrace_meta_lock);
	mutex_enter(&dtrace_lock);

	if (old == dtrace_meta_pid) {
		pp = &dtrace_meta_pid;
	} else {
		panic("attempt to unregister non-existent "
		    "dtrace meta-provider %p\n", (void *)old);
	}

	if (old->dtm_count != 0) {
		mutex_exit(&dtrace_lock);
		mutex_exit(&dtrace_meta_lock);
		return (EBUSY);
	}

	*pp = NULL;

	mutex_exit(&dtrace_lock);
	mutex_exit(&dtrace_meta_lock);

	kmem_free(old->dtm_name, strlen(old->dtm_name) + 1);
	kmem_free(old, sizeof (dtrace_meta_t));

	return (0);
}