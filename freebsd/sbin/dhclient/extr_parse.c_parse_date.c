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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; scalar_t__ tm_yday; scalar_t__ tm_isdst; void* tm_wday; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COLON ; 
 int NUMBER ; 
 int SEMI ; 
 int SLASH ; 
 void* atoi (char*) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

time_t
parse_date(FILE *cfile)
{
	static int months[11] = { 31, 59, 90, 120, 151, 181,
	    212, 243, 273, 304, 334 };
	int guess, token;
	struct tm tm;
	char *val;

	/* Day of week... */
	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("numeric day of week expected.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}
	tm.tm_wday = atoi(val);

	/* Year... */
	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("numeric year expected.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}
	tm.tm_year = atoi(val);
	if (tm.tm_year > 1900)
		tm.tm_year -= 1900;

	/* Slash separating year from month... */
	token = next_token(&val, cfile);
	if (token != SLASH) {
		parse_warn("expected slash separating year from month.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}

	/* Month... */
	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("numeric month expected.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}
	tm.tm_mon = atoi(val) - 1;

	/* Slash separating month from day... */
	token = next_token(&val, cfile);
	if (token != SLASH) {
		parse_warn("expected slash separating month from day.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}

	/* Month... */
	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("numeric day of month expected.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}
	tm.tm_mday = atoi(val);

	/* Hour... */
	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("numeric hour expected.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}
	tm.tm_hour = atoi(val);

	/* Colon separating hour from minute... */
	token = next_token(&val, cfile);
	if (token != COLON) {
		parse_warn("expected colon separating hour from minute.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}

	/* Minute... */
	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("numeric minute expected.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}
	tm.tm_min = atoi(val);

	/* Colon separating minute from second... */
	token = next_token(&val, cfile);
	if (token != COLON) {
		parse_warn("expected colon separating hour from minute.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}

	/* Minute... */
	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("numeric minute expected.");
		if (token != SEMI)
			skip_to_semi(cfile);
		return (0);
	}
	tm.tm_sec = atoi(val);
	tm.tm_isdst = 0;

	/* XXX: We assume that mktime does not use tm_yday. */
	tm.tm_yday = 0;

	/* Make sure the date ends in a semicolon... */
	token = next_token(&val, cfile);
	if (token != SEMI) {
		parse_warn("semicolon expected.");
		skip_to_semi(cfile);
		return (0);
	}

	/* Guess the time value... */
	guess = ((((((365 * (tm.tm_year - 70) +	/* Days in years since '70 */
		    (tm.tm_year - 69) / 4 +	/* Leap days since '70 */
		    (tm.tm_mon			/* Days in months this year */
		    ? months[tm.tm_mon - 1]
		    : 0) +
		    (tm.tm_mon > 1 &&		/* Leap day this year */
		    !((tm.tm_year - 72) & 3)) +
		    tm.tm_mday - 1) * 24) +	/* Day of month */
		    tm.tm_hour) * 60) +
		    tm.tm_min) * 60) + tm.tm_sec;

	/*
	 * This guess could be wrong because of leap seconds or other
	 * weirdness we don't know about that the system does.   For
	 * now, we're just going to accept the guess, but at some point
	 * it might be nice to do a successive approximation here to get
	 * an exact value.   Even if the error is small, if the server
	 * is restarted frequently (and thus the lease database is
	 * reread), the error could accumulate into something
	 * significant.
	 */
	return (guess);
}