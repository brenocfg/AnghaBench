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
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

void mad_dump_linkspeedext(char *buf, int bufsz, void *val, int valsz)
{
	int speed = *(int *)val;

	switch (speed) {
	case 0:
		snprintf(buf, bufsz, "No Extended Speed");
		break;
	case 1:
		snprintf(buf, bufsz, "14.0625 Gbps");
		break;
	case 2:
		snprintf(buf, bufsz, "25.78125 Gbps");
		break;
	default:
		snprintf(buf, bufsz, "undefined (%d)", speed);
		break;
	}
}