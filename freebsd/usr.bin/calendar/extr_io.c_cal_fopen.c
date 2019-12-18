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
 char** calendarHomes ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* getenv (char*) ; 
 unsigned int nitems (char**) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static FILE *
cal_fopen(const char *file)
{
	FILE *fp;
	char *home = getenv("HOME");
	unsigned int i;

	if (home == NULL || *home == '\0') {
		warnx("Cannot get home directory");
		return (NULL);
	}

	if (chdir(home) != 0) {
		warnx("Cannot enter home directory");
		return (NULL);
	}

	for (i = 0; i < nitems(calendarHomes); i++) {
		if (chdir(calendarHomes[i]) != 0)
			continue;

		if ((fp = fopen(file, "r")) != NULL)
			return (fp);
	}

	warnx("can't open calendar file \"%s\"", file);

	return (NULL);
}