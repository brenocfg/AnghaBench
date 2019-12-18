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
struct if_clone {char const* ifc_name; } ;

/* Variables and functions */
 int strlen (char const*) ; 

__attribute__((used)) static int
ifc_simple_match(struct if_clone *ifc, const char *name)
{
	const char *cp;
	int i;
	
	/* Match the name */
	for (cp = name, i = 0; i < strlen(ifc->ifc_name); i++, cp++) {
		if (ifc->ifc_name[i] != *cp)
			return (0);
	}

	/* Make sure there's a unit number or nothing after the name */
	for (; *cp != '\0'; cp++) {
		if (*cp < '0' || *cp > '9')
			return (0);
	}

	return (1);
}