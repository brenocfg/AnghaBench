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
 int VE_TRY ; 
 int VE_WANT ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
severity_guess(const char *filename)
{
	const char *cp;

	/* Some files like *.conf and *.hints may be unsigned */
	if ((cp = strrchr(filename, '.'))) {
		if (strcmp(cp, ".conf") == 0 ||
		    strcmp(cp, ".cookie") == 0 ||
			strcmp(cp, ".hints") == 0)
			return (VE_TRY);
	}
	return (VE_WANT);
}