#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tpacket_stats_v3 {int dummy; } ;
struct tpacket_stats {scalar_t__ tp_drops; scalar_t__ tp_packets; } ;
struct pcap_stat {int /*<<< orphan*/  ps_ifdrop; scalar_t__ ps_drop; int /*<<< orphan*/  ps_recv; } ;
struct pcap_linux {long proc_dropped; struct pcap_stat stat; int /*<<< orphan*/  packets_read; int /*<<< orphan*/  device; } ;
typedef  int socklen_t ;
struct TYPE_4__ {scalar_t__ promisc; } ;
struct TYPE_5__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; TYPE_1__ opt; struct pcap_linux* priv; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  PACKET_STATISTICS ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 scalar_t__ errno ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tpacket_stats*,int*) ; 
 long linux_if_drops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 

__attribute__((used)) static int
pcap_stats_linux(pcap_t *handle, struct pcap_stat *stats)
{
	struct pcap_linux *handlep = handle->priv;
#ifdef HAVE_STRUCT_TPACKET_STATS
#ifdef HAVE_TPACKET3
	/*
	 * For sockets using TPACKET_V1 or TPACKET_V2, the extra
	 * stuff at the end of a struct tpacket_stats_v3 will not
	 * be filled in, and we don't look at it so this is OK even
	 * for those sockets.  In addition, the PF_PACKET socket
	 * code in the kernel only uses the length parameter to
	 * compute how much data to copy out and to indicate how
	 * much data was copied out, so it's OK to base it on the
	 * size of a struct tpacket_stats.
	 *
	 * XXX - it's probably OK, in fact, to just use a
	 * struct tpacket_stats for V3 sockets, as we don't
	 * care about the tp_freeze_q_cnt stat.
	 */
	struct tpacket_stats_v3 kstats;
#else /* HAVE_TPACKET3 */
	struct tpacket_stats kstats;
#endif /* HAVE_TPACKET3 */
	socklen_t len = sizeof (struct tpacket_stats);
#endif /* HAVE_STRUCT_TPACKET_STATS */

	long if_dropped = 0;

	/*
	 *	To fill in ps_ifdrop, we parse /proc/net/dev for the number
	 */
	if (handle->opt.promisc)
	{
		if_dropped = handlep->proc_dropped;
		handlep->proc_dropped = linux_if_drops(handlep->device);
		handlep->stat.ps_ifdrop += (handlep->proc_dropped - if_dropped);
	}

#ifdef HAVE_STRUCT_TPACKET_STATS
	/*
	 * Try to get the packet counts from the kernel.
	 */
	if (getsockopt(handle->fd, SOL_PACKET, PACKET_STATISTICS,
			&kstats, &len) > -1) {
		/*
		 * On systems where the PACKET_STATISTICS "getsockopt()"
		 * argument is supported on PF_PACKET sockets:
		 *
		 *	"ps_recv" counts only packets that *passed* the
		 *	filter, not packets that didn't pass the filter.
		 *	This includes packets later dropped because we
		 *	ran out of buffer space.
		 *
		 *	"ps_drop" counts packets dropped because we ran
		 *	out of buffer space.  It doesn't count packets
		 *	dropped by the interface driver.  It counts only
		 *	packets that passed the filter.
		 *
		 *	See above for ps_ifdrop.
		 *
		 *	Both statistics include packets not yet read from
		 *	the kernel by libpcap, and thus not yet seen by
		 *	the application.
		 *
		 * In "linux/net/packet/af_packet.c", at least in the
		 * 2.4.9 kernel, "tp_packets" is incremented for every
		 * packet that passes the packet filter *and* is
		 * successfully queued on the socket; "tp_drops" is
		 * incremented for every packet dropped because there's
		 * not enough free space in the socket buffer.
		 *
		 * When the statistics are returned for a PACKET_STATISTICS
		 * "getsockopt()" call, "tp_drops" is added to "tp_packets",
		 * so that "tp_packets" counts all packets handed to
		 * the PF_PACKET socket, including packets dropped because
		 * there wasn't room on the socket buffer - but not
		 * including packets that didn't pass the filter.
		 *
		 * In the BSD BPF, the count of received packets is
		 * incremented for every packet handed to BPF, regardless
		 * of whether it passed the filter.
		 *
		 * We can't make "pcap_stats()" work the same on both
		 * platforms, but the best approximation is to return
		 * "tp_packets" as the count of packets and "tp_drops"
		 * as the count of drops.
		 *
		 * Keep a running total because each call to
		 *    getsockopt(handle->fd, SOL_PACKET, PACKET_STATISTICS, ....
		 * resets the counters to zero.
		 */
		handlep->stat.ps_recv += kstats.tp_packets;
		handlep->stat.ps_drop += kstats.tp_drops;
		*stats = handlep->stat;
		return 0;
	}
	else
	{
		/*
		 * If the error was EOPNOTSUPP, fall through, so that
		 * if you build the library on a system with
		 * "struct tpacket_stats" and run it on a system
		 * that doesn't, it works as it does if the library
		 * is built on a system without "struct tpacket_stats".
		 */
		if (errno != EOPNOTSUPP) {
			pcap_fmt_errmsg_for_errno(handle->errbuf,
			    PCAP_ERRBUF_SIZE, errno, "pcap_stats");
			return -1;
		}
	}
#endif
	/*
	 * On systems where the PACKET_STATISTICS "getsockopt()" argument
	 * is not supported on PF_PACKET sockets:
	 *
	 *	"ps_recv" counts only packets that *passed* the filter,
	 *	not packets that didn't pass the filter.  It does not
	 *	count packets dropped because we ran out of buffer
	 *	space.
	 *
	 *	"ps_drop" is not supported.
	 *
	 *	"ps_ifdrop" is supported. It will return the number
	 *	of drops the interface reports in /proc/net/dev,
	 *	if that is available.
	 *
	 *	"ps_recv" doesn't include packets not yet read from
	 *	the kernel by libpcap.
	 *
	 * We maintain the count of packets processed by libpcap in
	 * "handlep->packets_read", for reasons described in the comment
	 * at the end of pcap_read_packet().  We have no idea how many
	 * packets were dropped by the kernel buffers -- but we know
	 * how many the interface dropped, so we can return that.
	 */

	stats->ps_recv = handlep->packets_read;
	stats->ps_drop = 0;
	stats->ps_ifdrop = handlep->stat.ps_ifdrop;
	return 0;
}