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

void mad_dump_node_type(char *buf, int bufsz, void *val, int valsz)
{
	int nodetype = *(int *)val;

	switch (nodetype) {
	case 1:
		snprintf(buf, bufsz, "Channel Adapter");
		break;
	case 2:
		snprintf(buf, bufsz, "Switch");
		break;
	case 3:
		snprintf(buf, bufsz, "Router");
		break;
	default:
		snprintf(buf, bufsz, "?(%d)?", nodetype);
		break;
	}
}