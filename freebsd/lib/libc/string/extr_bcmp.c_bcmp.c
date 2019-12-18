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

int
bcmp(const void *b1, const void *b2, size_t length)
{
	char *p1, *p2;

	if (length == 0)
		return (0);
	p1 = (char *)b1;
	p2 = (char *)b2;
	do
		if (*p1++ != *p2++)
			break;
	while (--length);
	return (length);
}