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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int
expand_syslog_m(const char *fmt, char **newfmt) {
	const char *str, *m;
	char *p, *np;

	p = strdup("");
	str = fmt;
	while ((m = strstr(str, "%m")) != NULL) {
		asprintf(&np, "%s%.*s%s", p, (int)(m - str),
		    str, strerror(errno));
		free(p);
		if (np == NULL) {
			errno = ENOMEM;
			return (-1);
		}
		p = np;
		str = m + 2;
	}
	
	if (*str != '\0') {
		asprintf(&np, "%s%s", p, str);
		free(p);
		if (np == NULL) {
			errno = ENOMEM;
			return (-1);
		}
		p = np;
	}

	*newfmt = p;
	return (0);
}