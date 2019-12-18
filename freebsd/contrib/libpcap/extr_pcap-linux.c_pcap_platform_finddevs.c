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
 int PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE ; 
 int PCAP_IF_RUNNING ; 
 int PCAP_IF_UP ; 
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  any_descr ; 
 int /*<<< orphan*/  can_be_bound ; 
 int /*<<< orphan*/  get_if_flags ; 
 int pcap_findalldevs_interfaces (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scan_proc_net_dev (int /*<<< orphan*/ *,char*) ; 
 int scan_sys_class_net (int /*<<< orphan*/ *,char*) ; 

int
pcap_platform_finddevs(pcap_if_list_t *devlistp, char *errbuf)
{
	int ret;

	/*
	 * Get the list of regular interfaces first.
	 */
	if (pcap_findalldevs_interfaces(devlistp, errbuf, can_be_bound,
	    get_if_flags) == -1)
		return (-1);	/* failure */

	/*
	 * Read "/sys/class/net", and add to the list of interfaces all
	 * interfaces listed there that we don't already have, because,
	 * on Linux, SIOCGIFCONF reports only interfaces with IPv4 addresses,
	 * and even getifaddrs() won't return information about
	 * interfaces with no addresses, so you need to read "/sys/class/net"
	 * to get the names of the rest of the interfaces.
	 */
	ret = scan_sys_class_net(devlistp, errbuf);
	if (ret == -1)
		return (-1);	/* failed */
	if (ret == 0) {
		/*
		 * No /sys/class/net; try reading /proc/net/dev instead.
		 */
		if (scan_proc_net_dev(devlistp, errbuf) == -1)
			return (-1);
	}

	/*
	 * Add the "any" device.
	 * As it refers to all network devices, not to any particular
	 * network device, the notion of "connected" vs. "disconnected"
	 * doesn't apply.
	 */
	if (add_dev(devlistp, "any",
	    PCAP_IF_UP|PCAP_IF_RUNNING|PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE,
	    any_descr, errbuf) == NULL)
		return (-1);

	return (0);
}