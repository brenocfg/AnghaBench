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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct snmp_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_ERR_GENERR ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int make_date_time (int /*<<< orphan*/ *,struct tm*,int) ; 
 int string_get (struct snmp_value*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
OS_getSystemDate(struct snmp_value *value)
{
	u_char s_date_time[11];
	struct tm tloc_tm;
	time_t tloc_time_t;
	struct timeval right_now;
	int string_len;

	if (gettimeofday(&right_now, NULL) < 0) {
		syslog(LOG_ERR, "gettimeofday failed: %m");
		return (SNMP_ERR_GENERR);
	}

	tloc_time_t = right_now.tv_sec;

	if (localtime_r(&tloc_time_t, &tloc_tm) == NULL) {
		syslog(LOG_ERR, "localtime_r() failed: %m ");
		return (SNMP_ERR_GENERR);
	}

	string_len = make_date_time(s_date_time, &tloc_tm,
	    right_now.tv_usec / 100000);

	return (string_get(value, s_date_time, string_len));
}