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

int within_depth(const char *name, int namelen,
			int depth, int max_depth)
{
	const char *cp = name, *cpe = name + namelen;

	while (cp < cpe) {
		if (*cp++ != '/')
			continue;
		depth++;
		if (depth > max_depth)
			return 0;
	}
	return 1;
}