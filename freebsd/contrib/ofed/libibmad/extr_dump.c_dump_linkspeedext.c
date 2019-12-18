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
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void dump_linkspeedext(char *buf, int bufsz, int speed)
{
	int n = 0;

	if (speed == 0) {
		sprintf(buf, "%d", speed);
		return;
	}

	if (speed & 0x1)
		n += snprintf(buf + n, bufsz - n, "14.0625 Gbps or ");
	if (n < bufsz && speed & 0x2)
		n += snprintf(buf + n, bufsz - n, "25.78125 Gbps or ");
	if (n >= bufsz) {
		if (bufsz > 3)
			buf[n - 4] = '\0';
		return;
	}

	if (speed >> 2) {
		n += snprintf(buf + n, bufsz - n, "undefined (%d)", speed);
		return;
	} else if (bufsz > 3)
		buf[n - 4] = '\0';
}