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

__attribute__((used)) static int
path_matches_noscheme(const char *cp)
{
	while (*cp) {
		if (*cp == ':')
			return 0;
		else if (*cp == '/')
			return 1;
		++cp;
	}
	return 1;
}