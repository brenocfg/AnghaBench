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

__attribute__((used)) static int only_spaces_and_periods(const char *path, size_t len, size_t skip)
{
	if (len < skip)
		return 0;
	len -= skip;
	path += skip;
	while (len-- > 0) {
		char c = *(path++);
		if (c != ' ' && c != '.')
			return 0;
	}
	return 1;
}