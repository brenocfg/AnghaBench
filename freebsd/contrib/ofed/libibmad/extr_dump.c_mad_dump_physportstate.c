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

void mad_dump_physportstate(char *buf, int bufsz, void *val, int valsz)
{
	int state = *(int *)val;

	switch (state) {
	case 0:
		snprintf(buf, bufsz, "NoChange");
		break;
	case 1:
		snprintf(buf, bufsz, "Sleep");
		break;
	case 2:
		snprintf(buf, bufsz, "Polling");
		break;
	case 3:
		snprintf(buf, bufsz, "Disabled");
		break;
	case 4:
		snprintf(buf, bufsz, "PortConfigurationTraining");
		break;
	case 5:
		snprintf(buf, bufsz, "LinkUp");
		break;
	case 6:
		snprintf(buf, bufsz, "LinkErrorRecovery");
		break;
	case 7:
		snprintf(buf, bufsz, "PhyTest");
		break;
	default:
		snprintf(buf, bufsz, "?(%d)", state);
	}
}