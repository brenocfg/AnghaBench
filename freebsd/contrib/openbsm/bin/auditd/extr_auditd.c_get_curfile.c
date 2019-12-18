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
 int /*<<< orphan*/  AUDIT_CURRENT_LINK ; 
 scalar_t__ MAXPATHLEN ; 
 int /*<<< orphan*/  auditd_log_err (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int readlink (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static char *
get_curfile(void)
{
	char *cf;
	int len;

	cf = malloc(MAXPATHLEN);
	if (cf == NULL) {
		auditd_log_err("malloc failed: %m");
		return (NULL);
	}

	len = readlink(AUDIT_CURRENT_LINK, cf, MAXPATHLEN - 1);
	if (len < 0) {
		free(cf);
		return (NULL);
	}

	/* readlink() doesn't terminate string. */
	cf[len] = '\0';

	return (cf);
}