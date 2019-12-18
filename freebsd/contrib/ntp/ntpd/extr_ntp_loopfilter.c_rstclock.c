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

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int EVNT_FSET ; 
 scalar_t__ clock_epoch ; 
 double clock_offset ; 
 scalar_t__ current_time ; 
 double last_offset ; 
 int /*<<< orphan*/  report_event (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int state ; 
 int /*<<< orphan*/  sys_poll ; 
 int /*<<< orphan*/  tc_counter ; 

__attribute__((used)) static void
rstclock(
	int	trans,		/* new state */
	double	offset		/* new offset */
	)
{
	DPRINTF(2, ("rstclock: mu %lu state %d poll %d count %d\n",
		    current_time - clock_epoch, trans, sys_poll,
		    tc_counter));
	if (trans != state && trans != EVNT_FSET)
		report_event(trans, NULL, NULL);
	state = trans;
	last_offset = clock_offset = offset;
	clock_epoch = current_time;
}