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
typedef  int /*<<< orphan*/  pcap_if_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE ; 
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*) ; 

int
dbus_findalldevs(pcap_if_list_t *devlistp, char *err_str)
{
	/*
	 * The notion of "connected" vs. "disconnected" doesn't apply.
	 * XXX - what about the notions of "up" and "running"?
	 */
	if (add_dev(devlistp, "dbus-system",
	    PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE, "D-Bus system bus",
	    err_str) == NULL)
		return -1;
	if (add_dev(devlistp, "dbus-session",
	    PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE, "D-Bus session bus",
	    err_str) == NULL)
		return -1;
	return 0;
}