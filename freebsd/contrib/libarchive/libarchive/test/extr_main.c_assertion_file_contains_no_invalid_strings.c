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

/* Variables and functions */
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* slurpfile (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * strstr (char*,char const*) ; 

int
assertion_file_contains_no_invalid_strings(const char *file, int line,
    const char *pathname, const char *strings[])
{
	char *buff;
	int i;

	buff = slurpfile(NULL, "%s", pathname);
	if (buff == NULL) {
		failure_start(file, line, "Can't read file: %s", pathname);
		failure_finish(NULL);
		return (0);
	}

	for (i = 0; strings[i] != NULL; ++i) {
		if (strstr(buff, strings[i]) != NULL) {
			failure_start(file, line, "Invalid string in %s: %s", pathname,
			    strings[i]);
			failure_finish(NULL);
			free(buff);
			return(0);
		}
	}

	free(buff);
	return (0);
}