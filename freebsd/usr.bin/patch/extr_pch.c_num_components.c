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
 char* strchr (char const*,char) ; 

__attribute__((used)) static size_t
num_components(const char *path)
{
	size_t n;
	const char *cp;

	for (n = 0, cp = path; (cp = strchr(cp, '/')) != NULL; n++, cp++) {
		while (*cp == '/')
			cp++;		/* skip consecutive slashes */
	}
	return n;
}