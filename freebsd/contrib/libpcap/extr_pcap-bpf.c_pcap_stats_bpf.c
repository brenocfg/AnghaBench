#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_stat {scalar_t__ ps_ifdrop; int /*<<< orphan*/  ps_drop; int /*<<< orphan*/  ps_recv; } ;
struct bpf_stat {int /*<<< orphan*/  bs_drop; int /*<<< orphan*/  bs_recv; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOCGSTATS ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcap_stats_bpf(pcap_t *p, struct pcap_stat *ps)
{
	struct bpf_stat s;

	/*
	 * "ps_recv" counts packets handed to the filter, not packets
	 * that passed the filter.  This includes packets later dropped
	 * because we ran out of buffer space.
	 *
	 * "ps_drop" counts packets dropped inside the BPF device
	 * because we ran out of buffer space.  It doesn't count
	 * packets dropped by the interface driver.  It counts
	 * only packets that passed the filter.
	 *
	 * Both statistics include packets not yet read from the kernel
	 * by libpcap, and thus not yet seen by the application.
	 */
	if (ioctl(p->fd, BIOCGSTATS, (caddr_t)&s) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "BIOCGSTATS");
		return (PCAP_ERROR);
	}

	ps->ps_recv = s.bs_recv;
	ps->ps_drop = s.bs_drop;
	ps->ps_ifdrop = 0;
	return (0);
}