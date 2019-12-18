#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_dtrace_helpers; } ;
typedef  TYPE_1__ proc_t ;
struct TYPE_6__ {void* dthps_actions; } ;
typedef  TYPE_2__ dtrace_helpers_t ;
typedef  int /*<<< orphan*/  dtrace_helper_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int DTRACE_NHELPER_ACTIONS ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_helpers ; 
 int /*<<< orphan*/  dtrace_lock ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_helpers_t *
dtrace_helpers_create(proc_t *p)
{
	dtrace_helpers_t *help;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(p->p_dtrace_helpers == NULL);

	help = kmem_zalloc(sizeof (dtrace_helpers_t), KM_SLEEP);
	help->dthps_actions = kmem_zalloc(sizeof (dtrace_helper_action_t *) *
	    DTRACE_NHELPER_ACTIONS, KM_SLEEP);

	p->p_dtrace_helpers = help;
	dtrace_helpers++;

	return (help);
}