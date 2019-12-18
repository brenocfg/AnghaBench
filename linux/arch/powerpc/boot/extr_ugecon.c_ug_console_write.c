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
 int /*<<< orphan*/  ug_putc (char) ; 

void ug_console_write(const char *buf, int len)
{
	char *b = (char *)buf;

	while (len--) {
		if (*b == '\n')
			ug_putc('\r');
		ug_putc(*b++);
	}
}