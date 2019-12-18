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
struct auth_xfer {struct auth_master* allow_notify_list; TYPE_1__* task_probe; } ;
struct auth_master {struct auth_master* next; } ;
struct TYPE_2__ {struct auth_master* masters; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_free_masters (struct auth_master*) ; 
 struct auth_master* auth_master_copy (struct auth_master*) ; 

__attribute__((used)) static void
probe_copy_masters_for_allow_notify(struct auth_xfer* xfr)
{
	struct auth_master* list = NULL, *last = NULL;
	struct auth_master* p;
	/* build up new list with copies */
	for(p = xfr->task_probe->masters; p; p=p->next) {
		struct auth_master* m = auth_master_copy(p);
		if(!m) {
			auth_free_masters(list);
			/* failed because of malloc failure, use old list */
			return;
		}
		m->next = NULL;
		if(last) last->next = m;
		if(!list) list = m;
		last = m;
	}
	/* success, replace list */
	auth_free_masters(xfr->allow_notify_list);
	xfr->allow_notify_list = list;
}