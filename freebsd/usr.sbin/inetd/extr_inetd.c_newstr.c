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
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
newstr(const char *cp)
{
	char *cr;

	if ((cr = strdup(cp != NULL ? cp : "")))
		return (cr);
	syslog(LOG_ERR, "strdup: %m");
	exit(EX_OSERR);
}