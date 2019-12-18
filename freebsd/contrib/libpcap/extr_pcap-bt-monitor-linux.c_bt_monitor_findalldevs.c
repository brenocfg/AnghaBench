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
 int /*<<< orphan*/  INTERFACE_NAME ; 
 int PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE ; 
 int PCAP_IF_WIRELESS ; 
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,char*) ; 

int
bt_monitor_findalldevs(pcap_if_list_t *devlistp, char *err_str)
{
    int         ret = 0;

    /*
     * Bluetooth is a wireless technology.
     *
     * This is a device to monitor all Bluetooth interfaces, so
     * there's no notion of "connected" or "disconnected", any
     * more than there's a notion of "connected" or "disconnected"
     * for the "any" device.
     */
    if (add_dev(devlistp, INTERFACE_NAME,
                PCAP_IF_WIRELESS|PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE,
                "Bluetooth Linux Monitor", err_str) == NULL)
    {
        ret = -1;
    }

    return ret;
}