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
typedef  int /*<<< orphan*/  vint64 ;
typedef  int /*<<< orphan*/  uint32_t ;
struct calendar {int dummy; } ;
typedef  int /*<<< orphan*/  ntpcal_split ;

/* Variables and functions */
 int /*<<< orphan*/  DAY_NTP_STARTS ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ntpcal_daysplit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntpcal_daysplit_to_date (struct calendar*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
caljulian(
	uint32_t		ntp,
	struct calendar *	jt
	)
{
	vint64		vlong;
	ntpcal_split	split;
	
	
	INSIST(NULL != jt);

	/*
	 * Unfold ntp time around current time into NTP domain. Split
	 * into days and seconds, shift days into CE domain and
	 * process the parts.
	 */
	vlong = ntpcal_ntp_to_ntp(ntp, NULL);
	split = ntpcal_daysplit(&vlong);
	ntpcal_daysplit_to_date(jt, &split, DAY_NTP_STARTS);
}