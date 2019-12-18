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
 int /*<<< orphan*/  BIOCLOCK ; 
 scalar_t__ DLT_PFLOG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PCAP_TO_MS ; 
 int /*<<< orphan*/  cur_snaplen ; 
 int /*<<< orphan*/  errbuf ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * hpcap ; 
 int /*<<< orphan*/  interface ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcap_close (int /*<<< orphan*/ *) ; 
 scalar_t__ pcap_datalink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcap_open_live (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_snapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pcap_filter () ; 
 int /*<<< orphan*/  snaplen ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
init_pcap(void)
{
	hpcap = pcap_open_live(interface, snaplen, 1, PCAP_TO_MS, errbuf);
	if (hpcap == NULL) {
		logmsg(LOG_ERR, "Failed to initialize: %s", errbuf);
		return (-1);
	}

	if (pcap_datalink(hpcap) != DLT_PFLOG) {
		logmsg(LOG_ERR, "Invalid datalink type");
		pcap_close(hpcap);
		hpcap = NULL;
		return (-1);
	}

	set_pcap_filter();

	cur_snaplen = snaplen = pcap_snapshot(hpcap);

	/* lock */
	if (ioctl(pcap_fileno(hpcap), BIOCLOCK) < 0) {
		logmsg(LOG_ERR, "BIOCLOCK: %s", strerror(errno));
		return (-1);
	}

	return (0);
}