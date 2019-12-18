#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* crontab; struct TYPE_4__* next; } ;
typedef  TYPE_1__ user ;
typedef  scalar_t__ pid_t ;
struct TYPE_5__ {int flags; scalar_t__ child; int /*<<< orphan*/  lastexit; struct TYPE_5__* next; } ;
typedef  TYPE_2__ entry ;
struct TYPE_6__ {TYPE_1__* head; } ;

/* Variables and functions */
 int INTERVAL ; 
 TYPE_3__ database ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
find_interval_entry(pid_t pid)
{
	user *u;
	entry *e;

	for (u = database.head;  u != NULL;  u = u->next) {
		for (e = u->crontab;  e != NULL;  e = e->next) {
			if ((e->flags & INTERVAL) && e->child == pid) {
				e->lastexit = time(NULL);
				e->child = 0;
				break;
			}
		}
	}
}