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
struct apm_event_info {size_t type; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMIO_NEXTEVENT ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 TYPE_1__* events ; 
 int exec_event_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct apm_event_info*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,size_t,...) ; 

void
proc_apmevent(int fd)
{
	struct apm_event_info apmevent;

	while (ioctl(fd, APMIO_NEXTEVENT, &apmevent) == 0) {
		int status;
		syslog(LOG_NOTICE, "apmevent %04x index %d\n",
			apmevent.type, apmevent.index);
		syslog(LOG_INFO, "apm event: %s", events[apmevent.type].name);
		if (fork() == 0) {
			status = exec_event_cmd(&events[apmevent.type]);
			exit(status);
		}
	}
}