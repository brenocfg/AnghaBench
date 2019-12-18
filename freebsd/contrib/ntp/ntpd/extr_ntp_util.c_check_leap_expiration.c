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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  leapfile_name ; 
 int leapsec_daystolive (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const* const,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
check_leap_expiration(
	int           is_daily_check,
	uint32_t      ntptime       ,
	const time_t *systime
	)
{
	static const char * const logPrefix = "leapsecond file";
	int  rc;

	/* test the expiration of the leap data and log with proper
	 * level and frequency (once/hour or once/day, depending on the
	 * state.
	 */
	rc = leapsec_daystolive(ntptime, systime);	
	if (rc == 0) {
		msyslog(LOG_WARNING,
			"%s ('%s'): will expire in less than one day",
			logPrefix, leapfile_name);
	} else if (is_daily_check && rc < 28) {
		if (rc < 0)
			msyslog(LOG_ERR,
				"%s ('%s'): expired less than %d day%s ago",
				logPrefix, leapfile_name, -rc, (rc == -1 ? "" : "s"));
		else
			msyslog(LOG_WARNING,
				"%s ('%s'): will expire in less than %d days",
				logPrefix, leapfile_name, 1+rc);
	}
}