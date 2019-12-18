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
 scalar_t__ snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void dump_linkwidth(char *buf, int bufsz, int width)
{
	int n = 0;

	if (width & 0x1)
		n += snprintf(buf + n, bufsz - n, "1X or ");
	if (n < bufsz && (width & 0x2))
		n += snprintf(buf + n, bufsz - n, "4X or ");
	if (n < bufsz && (width & 0x4))
		n += snprintf(buf + n, bufsz - n, "8X or ");
	if (n < bufsz && (width & 0x8))
		n += snprintf(buf + n, bufsz - n, "12X or ");
	if (n < bufsz && (width & 0x10))
		n += snprintf(buf + n, bufsz - n, "2X or ");

	if (n >= bufsz)
		return;
	else if (width == 0 || (width >> 5))
		snprintf(buf + n, bufsz - n, "undefined (%d)", width);
	else if (bufsz > 3)
		buf[n - 4] = '\0';
}