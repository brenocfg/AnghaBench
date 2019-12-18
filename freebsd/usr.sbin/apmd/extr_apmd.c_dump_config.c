#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct event_cmd {char* name; TYPE_1__* op; struct event_cmd* next; } ;
struct battery_watch_event {int level; scalar_t__ type; scalar_t__ direction; struct event_cmd* cmdlist; struct battery_watch_event* next; } ;
struct TYPE_4__ {char* name; struct event_cmd* cmdlist; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dump ) (struct event_cmd*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ BATTERY_CHARGING ; 
 scalar_t__ BATTERY_PERCENT ; 
 int EVENT_MAX ; 
 struct battery_watch_event* battery_watch_list ; 
 TYPE_2__* events ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct event_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct event_cmd*,int /*<<< orphan*/ ) ; 

void
dump_config(void)
{
	int i;
	struct battery_watch_event *q;

	for (i = 0; i < EVENT_MAX; i++) {
		struct event_cmd * p;
		if ((p = events[i].cmdlist)) {
			fprintf(stderr, "apm_event %s {\n", events[i].name);
			for ( ; p ; p = p->next) {
				fprintf(stderr, "\t%s", p->name);
				if (p->op->dump)
					p->op->dump(p, stderr);
				fprintf(stderr, ";\n");
			}
			fprintf(stderr, "}\n");
		}
	}
	for (q = battery_watch_list ; q != NULL ; q = q -> next) {
		struct event_cmd * p;
		fprintf(stderr, "apm_battery %d%s %s {\n",
			q -> level,
			(q -> type == BATTERY_PERCENT)?"%":"m",
			(q -> direction == BATTERY_CHARGING)?"charging":
				"discharging");
		for ( p = q -> cmdlist; p ; p = p->next) {
			fprintf(stderr, "\t%s", p->name);
			if (p->op->dump)
				p->op->dump(p, stderr);
			fprintf(stderr, ";\n");
		}
		fprintf(stderr, "}\n");
	}
}