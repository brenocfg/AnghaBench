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
struct rusage {int /*<<< orphan*/  ru_utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int MaxIterations ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  name2 ; 
 int /*<<< orphan*/  nameValuePair ; 
 int putenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_time (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int setenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  value1 ; 
 int /*<<< orphan*/  value2 ; 

int
main(int argc, char **argv)
{
	int iterations;
	struct rusage endUsage;
	struct rusage startUsage;

	/*
	 * getenv() on the existing environment.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		if (getenv(name) == NULL)
			err(EXIT_FAILURE, "getenv(name)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("getenv(name)", &startUsage.ru_utime, &endUsage.ru_utime);


	/*
	 * setenv() a variable with a large value.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		if (setenv(name, value1, 1) == -1)
			err(EXIT_FAILURE, "setenv(name, value1, 1)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("setenv(name, value1, 1)", &startUsage.ru_utime,
	    &endUsage.ru_utime);


	/*
	 * getenv() the new variable on the new environment.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		/* Set large value to variable. */
		if (getenv(name) == NULL)
			err(EXIT_FAILURE, "getenv(name)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("getenv(name)", &startUsage.ru_utime, &endUsage.ru_utime);


	/*
	 * getenv() a different variable on the new environment.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		/* Set large value to variable. */
		if (getenv(name2) == NULL)
			err(EXIT_FAILURE, "getenv(name2)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("getenv(name2)", &startUsage.ru_utime, &endUsage.ru_utime);


	/*
	 * setenv() a variable with a small value.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		if (setenv(name, value2, 1) == -1)
			err(EXIT_FAILURE, "setenv(name, value2, 1)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("setenv(name, value2, 1)", &startUsage.ru_utime,
	    &endUsage.ru_utime);


	/*
	 * getenv() a different variable on the new environment.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		/* Set large value to variable. */
		if (getenv(name2) == NULL)
			err(EXIT_FAILURE, "getenv(name)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("getenv(name)", &startUsage.ru_utime, &endUsage.ru_utime);


	/*
	 * getenv() a different variable on the new environment.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		/* Set large value to variable. */
		if (getenv(name2) == NULL)
			err(EXIT_FAILURE, "getenv(name2)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("getenv(name2)", &startUsage.ru_utime, &endUsage.ru_utime);


	/*
	 * putenv() a variable with a small value.
	 */
	getrusage(RUSAGE_SELF, &startUsage);

	/* Iterate over setting variable. */
	for (iterations = 0; iterations < MaxIterations; iterations++)
		if (putenv(nameValuePair) == -1)
			err(EXIT_FAILURE, "putenv(nameValuePair)");

	getrusage(RUSAGE_SELF, &endUsage);

	report_time("putenv(nameValuePair)", &startUsage.ru_utime,
	    &endUsage.ru_utime);


	exit(EXIT_SUCCESS);
}