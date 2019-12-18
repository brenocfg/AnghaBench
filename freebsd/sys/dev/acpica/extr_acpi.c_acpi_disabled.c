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
 int /*<<< orphan*/  freeenv (char*) ; 
 scalar_t__ isspace (char) ; 
 char* kern_getenv (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
acpi_disabled(char *subsys)
{
    char	*cp, *env;
    int		len;

    if ((env = kern_getenv("debug.acpi.disabled")) == NULL)
	return (0);
    if (strcmp(env, "all") == 0) {
	freeenv(env);
	return (1);
    }

    /* Scan the disable list, checking for a match. */
    cp = env;
    for (;;) {
	while (*cp != '\0' && isspace(*cp))
	    cp++;
	if (*cp == '\0')
	    break;
	len = 0;
	while (cp[len] != '\0' && !isspace(cp[len]))
	    len++;
	if (strncmp(cp, subsys, len) == 0) {
	    freeenv(env);
	    return (1);
	}
	cp += len;
    }
    freeenv(env);

    return (0);
}