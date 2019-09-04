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
typedef  int time_t ;
struct tm {int tm_isdst; } ;
typedef  int /*<<< orphan*/  git_signature ;

/* Variables and functions */
 scalar_t__ difftime (int,int /*<<< orphan*/ ) ; 
 scalar_t__ git_signature_new (int /*<<< orphan*/ **,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 struct tm* p_gmtime_r (int*,struct tm*) ; 
 int /*<<< orphan*/  time (int*) ; 

int git_signature_now(git_signature **sig_out, const char *name, const char *email)
{
	time_t now;
	time_t offset;
	struct tm *utc_tm;
	git_signature *sig;
	struct tm _utc;

	*sig_out = NULL;

	/*
	 * Get the current time as seconds since the epoch and
	 * transform that into a tm struct containing the time at
	 * UTC. Give that to mktime which considers it a local time
	 * (tm_isdst = -1 asks it to take DST into account) and gives
	 * us that time as seconds since the epoch. The difference
	 * between its return value and 'now' is our offset to UTC.
	 */
	time(&now);
	utc_tm = p_gmtime_r(&now, &_utc);
	utc_tm->tm_isdst = -1;
	offset = (time_t)difftime(now, mktime(utc_tm));
	offset /= 60;

	if (git_signature_new(&sig, name, email, now, (int)offset) < 0)
		return -1;

	*sig_out = sig;

	return 0;
}