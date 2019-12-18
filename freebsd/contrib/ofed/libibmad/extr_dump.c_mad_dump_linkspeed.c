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

void mad_dump_linkspeed(char *buf, int bufsz, void *val, int valsz)
{
	int speed = *(int *)val;

	switch (speed) {
	case 0:
		snprintf(buf, bufsz, "Extended speed");
		break;
	case 1:
		snprintf(buf, bufsz, "2.5 Gbps");
		break;
	case 2:
		snprintf(buf, bufsz, "5.0 Gbps");
		break;
	case 4:
		snprintf(buf, bufsz, "10.0 Gbps");
		break;
	default:
		snprintf(buf, bufsz, "undefined (%d)", speed);
		break;
	}
}