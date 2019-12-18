#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* crontab; struct TYPE_5__* next; } ;
typedef  TYPE_1__ user ;
struct TYPE_6__ {int flags; struct TYPE_6__* next; } ;
typedef  TYPE_2__ entry ;
struct TYPE_7__ {TYPE_1__* head; } ;
typedef  TYPE_3__ cron_db ;

/* Variables and functions */
 int INTERVAL ; 
 int SEC_RES ; 

__attribute__((used)) static int
run_at_secres(cron_db *db)
{
	user *u;
	entry *e;

	for (u = db->head;  u != NULL;  u = u->next) {
		for (e = u->crontab;  e != NULL;  e = e->next) {
			if ((e->flags & (SEC_RES | INTERVAL)) != 0)
				return 1;
		}
	}
	return 0;
}