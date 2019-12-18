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

__attribute__((used)) static int compare_prefix(const char *refname, const char *prefix)
{
	while (*prefix) {
		if (*refname != *prefix)
			return ((unsigned char)*refname < (unsigned char)*prefix) ? -1 : +1;

		refname++;
		prefix++;
	}

	return 0;
}