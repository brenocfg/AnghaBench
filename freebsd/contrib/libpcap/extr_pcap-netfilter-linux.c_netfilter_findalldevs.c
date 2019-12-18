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
 int /*<<< orphan*/  AF_NETLINK ; 
 scalar_t__ EAFNOSUPPORT ; 
 scalar_t__ EPROTONOSUPPORT ; 
 int /*<<< orphan*/  NETLINK_NETFILTER ; 
 int /*<<< orphan*/  NFLOG_IFACE ; 
 int /*<<< orphan*/  NFQUEUE_IFACE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
netfilter_findalldevs(pcap_if_list_t *devlistp, char *err_str)
{
	int sock;

	sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_NETFILTER);
	if (sock < 0) {
		/* if netlink is not supported this is not fatal */
		if (errno == EAFNOSUPPORT || errno == EPROTONOSUPPORT)
			return 0;
		pcap_fmt_errmsg_for_errno(err_str, PCAP_ERRBUF_SIZE,
		    errno, "Can't open netlink socket");
		return -1;
	}
	close(sock);

	/*
	 * The notion of "connected" vs. "disconnected" doesn't apply.
	 * XXX - what about "up" and "running"?
	 */
	if (add_dev(devlistp, NFLOG_IFACE,
	    PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE,
	    "Linux netfilter log (NFLOG) interface", err_str) == NULL)
		return -1;
	if (add_dev(devlistp, NFQUEUE_IFACE,
	    PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE,
	    "Linux netfilter queue (NFQUEUE) interface", err_str) == NULL)
		return -1;
	return 0;
}