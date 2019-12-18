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

__attribute__((used)) static char *
slow_strchr(char *buf, int ch)
{
	unsigned char c = 1;

	ch &= 0xff;

	for (; c != 0; buf++) {
		c = *buf;
		if (c == ch)
			return buf;
	}
	return 0;
}