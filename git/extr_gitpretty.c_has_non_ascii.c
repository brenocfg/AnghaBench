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
 scalar_t__ non_ascii (int) ; 

int has_non_ascii(const char *s)
{
	int ch;
	if (!s)
		return 0;
	while ((ch = *s++) != '\0') {
		if (non_ascii(ch))
			return 1;
	}
	return 0;
}