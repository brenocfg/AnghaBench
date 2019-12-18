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
struct TYPE_6__ {size_t action; TYPE_1__* ccache; int /*<<< orphan*/  backoff_time; int /*<<< orphan*/  fire_count; int /*<<< orphan*/  expire_time; int /*<<< orphan*/  fire_time; } ;
typedef  TYPE_2__ kcm_event ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * action_strings ; 
 int /*<<< orphan*/  kcm_log (int,char*,char*,TYPE_2__*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_times (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
log_event(kcm_event *event, char *msg)
{
    char fire_time[64], expire_time[64];

    print_times(event->fire_time, fire_time);
    print_times(event->expire_time, expire_time);

    kcm_log(7, "%s event %08x: fire_time %s fire_count %d expire_time %s "
	    "backoff_time %d action %s cache %s",
	    msg, event, fire_time, event->fire_count, expire_time,
	    event->backoff_time, action_strings[event->action],
	    event->ccache->name);
}