#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sysevent_t ;
typedef  int /*<<< orphan*/  sysevent_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  SE_SLEEP ; 
 int /*<<< orphan*/  log_sysevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysevent_free (int /*<<< orphan*/ *) ; 

void
spa_event_post(sysevent_t *ev)
{
#ifdef _KERNEL
	sysevent_id_t		eid;

	(void) log_sysevent(ev, SE_SLEEP, &eid);
	sysevent_free(ev);
#endif
}