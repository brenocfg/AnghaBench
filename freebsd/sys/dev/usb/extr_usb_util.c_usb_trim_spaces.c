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

void
usb_trim_spaces(char *p)
{
	char *q;
	char *e;

	if (p == NULL)
		return;
	q = e = p;
	while (*q == ' ')		/* skip leading spaces */
		q++;
	while ((*p = *q++))		/* copy string */
		if (*p++ != ' ')	/* remember last non-space */
			e = p;
	*e = 0;				/* kill trailing spaces */
}