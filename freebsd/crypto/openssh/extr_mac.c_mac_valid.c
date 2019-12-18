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
 int /*<<< orphan*/  MAC_SEP ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mac_setup (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,int /*<<< orphan*/ ) ; 

int
mac_valid(const char *names)
{
	char *maclist, *cp, *p;

	if (names == NULL || strcmp(names, "") == 0)
		return 0;
	if ((maclist = cp = strdup(names)) == NULL)
		return 0;
	for ((p = strsep(&cp, MAC_SEP)); p && *p != '\0';
	    (p = strsep(&cp, MAC_SEP))) {
		if (mac_setup(NULL, p) < 0) {
			free(maclist);
			return 0;
		}
	}
	free(maclist);
	return 1;
}