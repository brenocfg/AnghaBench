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
 scalar_t__ ENOENT ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 char const* SYSCTL_SCRIPTS ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strsep (char**,char*) ; 
 int sysctlbyname (char const*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ddb_list_scripts(const char *scriptname)
{
	char *buffer, *line, *nextline;
	char *line_script, *line_scriptname;
	size_t buflen, len;
	int ret;

repeat:
	if (sysctlbyname(SYSCTL_SCRIPTS, NULL, &buflen, NULL, 0) < 0)
		err(EX_OSERR, "sysctl: %s", SYSCTL_SCRIPTS);
	if (buflen == 0)
		return;
	buffer = malloc(buflen);
	if (buffer == NULL)
		err(EX_OSERR, "malloc");
	bzero(buffer, buflen);
	len = buflen;
	ret = sysctlbyname(SYSCTL_SCRIPTS, buffer, &len, NULL, 0);
	if (ret < 0 && errno != ENOMEM)
		err(EX_OSERR, "sysctl: %s", SYSCTL_SCRIPTS);
	if (ret < 0) {
		free(buffer);
		goto repeat;
	}

	/*
	 * We nul'd the buffer before calling sysctl(), so at worst empty.
	 *
	 * If a specific script hasn't been requested, print it all.
	 */
	if (scriptname == NULL) {
		printf("%s", buffer);
		free(buffer);
		return;
	}

	/*
	 * If a specific script has been requested, we have to parse the
	 * string to find it.
	 */
	nextline = buffer;
	while ((line = strsep(&nextline, "\n")) != NULL) {
		line_script = line;
		line_scriptname = strsep(&line_script, "=");
		if (line_script == NULL)
			continue;
		if (strcmp(scriptname, line_scriptname) != 0)
			continue;
		printf("%s\n", line_script);
		break;
	}
	if (line == NULL) {
		errno = ENOENT;
		err(EX_DATAERR, "%s", scriptname);
	}
	free(buffer);
}