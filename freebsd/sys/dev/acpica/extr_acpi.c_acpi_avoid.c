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
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 char* acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 scalar_t__ isspace (char) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int
acpi_avoid(ACPI_HANDLE handle)
{
    char	*cp, *env, *np;
    int		len;

    np = acpi_name(handle);
    if (*np == '\\')
	np++;
    if ((env = kern_getenv("debug.acpi.avoid")) == NULL)
	return (0);

    /* Scan the avoid list checking for a match */
    cp = env;
    for (;;) {
	while (*cp != 0 && isspace(*cp))
	    cp++;
	if (*cp == 0)
	    break;
	len = 0;
	while (cp[len] != 0 && !isspace(cp[len]))
	    len++;
	if (!strncmp(cp, np, len)) {
	    freeenv(env);
	    return(1);
	}
	cp += len;
    }
    freeenv(env);

    return (0);
}