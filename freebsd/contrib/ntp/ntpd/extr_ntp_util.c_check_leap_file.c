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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  check_leap_expiration (int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ have_leapfile ; 
 scalar_t__* leapfile_name ; 
 int /*<<< orphan*/  leapfile_stat ; 
 scalar_t__ leapsec_load_file (scalar_t__*,int /*<<< orphan*/ *,int,int) ; 

void
check_leap_file(
	int           is_daily_check,
	uint32_t      ntptime       ,
	const time_t *systime
	)
{
	/* just do nothing if there is no leap file */
	if ( ! (leapfile_name && *leapfile_name))
		return;
	
	/* try to load leapfile, force it if no leapfile loaded yet */
	if (leapsec_load_file(
		    leapfile_name, &leapfile_stat,
		    !have_leapfile, is_daily_check))
		have_leapfile = TRUE;
	else if (!have_leapfile)
		return;

	check_leap_expiration(is_daily_check, ntptime, systime);
}