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
typedef  int u_int ;
struct event_cmd {int dummy; } ;
struct battery_watch_event {struct battery_watch_event* next; struct event_cmd* cmdlist; } ;
struct TYPE_2__ {struct event_cmd* cmdlist; } ;

/* Variables and functions */
 int EVENT_MAX ; 
 int /*<<< orphan*/  apmctl_fd ; 
 struct battery_watch_event* battery_watch_list ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 TYPE_1__* events ; 
 int /*<<< orphan*/  free (struct battery_watch_event*) ; 
 int /*<<< orphan*/  free_event_cmd_list (struct event_cmd*) ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 

void
destroy_config(void)
{
	int i;
	struct battery_watch_event *q;

	/* disable events */
	for (i = 0; i < EVENT_MAX; i++) {
		if (events[i].cmdlist) {
			u_int event_type = i;
			if (write(apmctl_fd, &event_type, sizeof(u_int)) == -1) {
				err(1, "cannot disable event 0x%x", event_type);
			}
		}
	}

	for (i = 0; i < EVENT_MAX; i++) {
		struct event_cmd * p;
		if ((p = events[i].cmdlist))
			free_event_cmd_list(p);
		events[i].cmdlist = NULL;
	}

	for( ; battery_watch_list; battery_watch_list = battery_watch_list -> next) {
		free_event_cmd_list(battery_watch_list->cmdlist);
		q = battery_watch_list->next;
		free(battery_watch_list);
		battery_watch_list = q;
	}
}