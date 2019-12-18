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
struct utmpx {int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_type; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ ARG ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_TIME ; 
#define  HOST_TYPE 131 
 int NO ; 
#define  REBOOT_TYPE 130 
 int /*<<< orphan*/  SHUTDOWN_TIME ; 
#define  TTY_TYPE 129 
#define  USER_TYPE 128 
 int YES ; 
 TYPE_1__* arglist ; 
 scalar_t__ snaptime ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
want(struct utmpx *bp)
{
	ARG *step;

	if (snaptime)
		return (NO);

	if (!arglist)
		return (YES);

	for (step = arglist; step; step = step->next)
		switch(step->type) {
		case REBOOT_TYPE:
			if (bp->ut_type == BOOT_TIME ||
			    bp->ut_type == SHUTDOWN_TIME)
				return (YES);
			break;
		case HOST_TYPE:
			if (!strcasecmp(step->name, bp->ut_host))
				return (YES);
			break;
		case TTY_TYPE:
			if (!strcmp(step->name, bp->ut_line))
				return (YES);
			break;
		case USER_TYPE:
			if (!strcmp(step->name, bp->ut_user))
				return (YES);
			break;
		}
	return (NO);
}