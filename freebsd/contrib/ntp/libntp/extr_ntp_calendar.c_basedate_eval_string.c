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
typedef  int u_short ;
typedef  scalar_t__ u_long ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ DAY_NTP_STARTS ; 
 scalar_t__ INT32_MAX ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ basedate_eval_buildstamp () ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ ntpcal_edate_to_eradays (int,int,int) ; 
 int sscanf (char const*,char*,...) ; 
 size_t strlen (char const*) ; 

int32_t
basedate_eval_string(
	const char * str
	)
{
	u_short	y,m,d;
	u_long	ned;
	int	rc, nc;
	size_t	sl;

	sl = strlen(str);	
	rc = sscanf(str, "%4hu-%2hu-%2hu%n", &y, &m, &d, &nc);
	if (rc == 3 && (size_t)nc == sl) {
		if (m >= 1 && m <= 12 && d >= 1 && d <= 31)
			return ntpcal_edate_to_eradays(y-1, m-1, d)
			    - DAY_NTP_STARTS;
		goto buildstamp;
	}

	rc = sscanf(str, "%lu%n", &ned, &nc);
	if (rc == 1 && (size_t)nc == sl) {
		if (ned <= INT32_MAX)
			return (int32_t)ned;
		goto buildstamp;
	}

  buildstamp:
	msyslog(LOG_WARNING,
		"basedate string \"%s\" invalid, build date substituted!",
		str);
	return basedate_eval_buildstamp();
}