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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOCK_SH ; 
 int /*<<< orphan*/  dumpdates ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  quit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readdumptimes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

void
initdumptimes(void)
{
	FILE *df;

	if ((df = fopen(dumpdates, "r")) == NULL) {
		if (errno != ENOENT) {
			msg("WARNING: cannot read %s: %s\n", dumpdates,
			    strerror(errno));
			return;
		}
		/*
		 * Dumpdates does not exist, make an empty one.
		 */
		msg("WARNING: no file `%s', making an empty one\n", dumpdates);
		if ((df = fopen(dumpdates, "w")) == NULL) {
			msg("WARNING: cannot create %s: %s\n", dumpdates,
			    strerror(errno));
			return;
		}
		(void) fclose(df);
		if ((df = fopen(dumpdates, "r")) == NULL) {
			quit("cannot read %s even after creating it: %s\n",
			    dumpdates, strerror(errno));
			/* NOTREACHED */
		}
	}
	(void) flock(fileno(df), LOCK_SH);
	readdumptimes(df);
	(void) fclose(df);
}