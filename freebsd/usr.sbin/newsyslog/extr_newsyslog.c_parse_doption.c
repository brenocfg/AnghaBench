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
typedef  int /*<<< orphan*/  TN ;

/* Variables and functions */
 int /*<<< orphan*/  PTM_PARSE_ISO8601 ; 
 int /*<<< orphan*/  dbg_at_times ; 
 int /*<<< orphan*/  dbg_timenow ; 
 int /*<<< orphan*/  ptime_init (int /*<<< orphan*/ *) ; 
 int ptime_relparse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
parse_doption(const char *doption)
{
	const char TN[] = "TN=";
	int res;

	if (strncmp(doption, TN, sizeof(TN) - 1) == 0) {
		/*
		 * The "TimeNow" debugging option.  This might be off
		 * by an hour when crossing a timezone change.
		 */
		dbg_timenow = ptime_init(NULL);
		res = ptime_relparse(dbg_timenow, PTM_PARSE_ISO8601,
		    time(NULL), doption + sizeof(TN) - 1);
		if (res == -2) {
			warnx("Non-existent time specified on -D %s", doption);
			return (0);			/* failure */
		} else if (res < 0) {
			warnx("Malformed time given on -D %s", doption);
			return (0);			/* failure */
		}
		return (1);			/* successfully parsed */

	}

	if (strcmp(doption, "ats") == 0) {
		dbg_at_times++;
		return (1);			/* successfully parsed */
	}

	/* XXX - This check could probably be dropped. */
	if ((strcmp(doption, "neworder") == 0) || (strcmp(doption, "oldorder")
	    == 0)) {
		warnx("NOTE: newsyslog always uses 'neworder'.");
		return (1);			/* successfully parsed */
	}

	warnx("Unknown -D (debug) option: '%s'", doption);
	return (0);				/* failure */
}