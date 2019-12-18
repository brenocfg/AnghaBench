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
 scalar_t__ bhnd_nv_isdigit (char const) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int) ; 

const char *
bhnd_nvram_trim_path_name(const char *name)
{
	char *endp;

	/* path alias prefix? (0:varname) */
	if (bhnd_nv_isdigit(*name)) {
		/* Parse '0...:' alias prefix, if it exists */
		strtoul(name, &endp, 10);
		if (endp != name && *endp == ':') {
			/* Variable name follows 0: prefix */
			return (endp+1);
		}
	}

	/* device path prefix? (pci/1/1/varname) */
	if ((endp = strrchr(name, '/')) != NULL) {
		/* Variable name follows the final path separator '/' */
		return (endp+1);
	}

	/* variable name is not prefixed */
	return (name);
}