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
 int ENAMETOOLONG ; 
 int MAXNAMELEN ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int
getpoolname(const char *osname, char *poolname)
{
	char *p;

	p = strchr(osname, '/');
	if (p == NULL) {
		if (strlen(osname) >= MAXNAMELEN)
			return (ENAMETOOLONG);
		(void) strcpy(poolname, osname);
	} else {
		if (p - osname >= MAXNAMELEN)
			return (ENAMETOOLONG);
		(void) strncpy(poolname, osname, p - osname);
		poolname[p - osname] = '\0';
	}
	return (0);
}