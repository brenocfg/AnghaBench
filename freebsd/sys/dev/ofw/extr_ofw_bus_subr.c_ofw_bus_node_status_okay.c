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
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int OFW_STATUS_LEN ; 
 int /*<<< orphan*/  OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bcmp (char*,char*,int) ; 

int
ofw_bus_node_status_okay(phandle_t node)
{
	char status[OFW_STATUS_LEN];
	int len;

	len = OF_getproplen(node, "status");
	if (len <= 0)
		return (1);

	OF_getprop(node, "status", status, OFW_STATUS_LEN);
	if ((len == 5 && (bcmp(status, "okay", len) == 0)) ||
	    (len == 3 && (bcmp(status, "ok", len))))
		return (1);

	return (0);
}