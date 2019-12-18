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
struct pcap_usb_linux {scalar_t__ packets_read; } ;
struct pcap_stat {scalar_t__ ps_ifdrop; int /*<<< orphan*/  ps_drop; scalar_t__ ps_recv; } ;
struct mon_bin_stats {int /*<<< orphan*/  dropped; scalar_t__ queued; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  errbuf; struct pcap_usb_linux* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  MON_IOCG_STATS ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mon_bin_stats*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usb_stats_linux_bin(pcap_t *handle, struct pcap_stat *stats)
{
	struct pcap_usb_linux *handlep = handle->priv;
	int ret;
	struct mon_bin_stats st;
	ret = ioctl(handle->fd, MON_IOCG_STATS, &st);
	if (ret < 0)
	{
		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "Can't read stats from fd %d", handle->fd);
		return -1;
	}

	stats->ps_recv = handlep->packets_read + st.queued;
	stats->ps_drop = st.dropped;
	stats->ps_ifdrop = 0;
	return 0;
}