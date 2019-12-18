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
 int ENOENT ; 
 int ENOMEM ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
kiconv_lookupconv(const char *drvname)
{
	size_t size;

	if (sysctlbyname("kern.iconv.drvlist", NULL, &size, NULL, 0) == -1)
		return (errno);
	if (size > 0) {
		char *drivers, *drvp;

		drivers = malloc(size);
		if (drivers == NULL)
			return (ENOMEM);
		if (sysctlbyname("kern.iconv.drvlist", drivers, &size, NULL, 0) == -1) {
			free(drivers);
			return (errno);
		}
		for (drvp = drivers; *drvp != '\0'; drvp += strlen(drvp) + 1)
			if (strcmp(drvp, drvname) == 0) {
				free(drivers);
				return (0);
			}
	}
	return (ENOENT);
}