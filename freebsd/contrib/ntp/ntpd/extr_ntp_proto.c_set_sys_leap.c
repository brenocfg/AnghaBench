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
typedef  scalar_t__ u_char ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 scalar_t__ LEAP_NOTINSYNC ; 
 scalar_t__ LEAP_NOWARNING ; 
 scalar_t__ leap_sec_in_progress ; 
 TYPE_1__ leap_smear ; 
 scalar_t__ sys_leap ; 
 scalar_t__ xmt_leap ; 

void
set_sys_leap(
	u_char new_sys_leap
	)
{
	sys_leap = new_sys_leap;
	xmt_leap = sys_leap;

	/*
	 * Under certain conditions we send faked leap bits to clients, so
	 * eventually change xmt_leap below, but never change LEAP_NOTINSYNC.
	 */
	if (xmt_leap != LEAP_NOTINSYNC) {
		if (leap_sec_in_progress) {
			/* always send "not sync" */
			xmt_leap = LEAP_NOTINSYNC;
		}
#ifdef LEAP_SMEAR
		else {
			/*
			 * If leap smear is enabled in general we must
			 * never send a leap second warning to clients,
			 * so make sure we only send "in sync".
			 */
			if (leap_smear.enabled)
				xmt_leap = LEAP_NOWARNING;
		}
#endif	/* LEAP_SMEAR */
	}
}