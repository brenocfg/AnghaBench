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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  _ENV_UTIL_COMPAT ; 
 int /*<<< orphan*/  _PATH_UTIL_COMPAT ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int readlink (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

int
check_utility_compat(const char *utility)
{
	char buf[PATH_MAX];
	char *p, *bp;
	int len;

	if ((p = getenv(_ENV_UTIL_COMPAT)) != NULL) {
		strlcpy(buf, p, sizeof buf);
	} else {
		if ((len = readlink(_PATH_UTIL_COMPAT, buf, sizeof(buf) - 1)) < 0)
			return 0;
		buf[len] = '\0';
	}
	if (buf[0] == '\0')
		return 1;

	bp = buf;
	while ((p = strsep(&bp, ",")) != NULL) {
		if (strcmp(p, utility) == 0)
			return 1;
	}
	return 0;
}