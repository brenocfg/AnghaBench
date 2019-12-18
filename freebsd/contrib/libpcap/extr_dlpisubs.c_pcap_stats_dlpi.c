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
struct pcap_stat {scalar_t__ ps_drop; int /*<<< orphan*/  ps_recv; } ;
struct pcap_dlpi {struct pcap_stat stat; } ;
struct TYPE_3__ {struct pcap_dlpi* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */

int
pcap_stats_dlpi(pcap_t *p, struct pcap_stat *ps)
{
	struct pcap_dlpi *pd = p->priv;

	/*
	 * "ps_recv" counts packets handed to the filter, not packets
	 * that passed the filter.  As filtering is done in userland,
	 * this would not include packets dropped because we ran out
	 * of buffer space; in order to make this more like other
	 * platforms (Linux 2.4 and later, BSDs with BPF), where the
	 * "packets received" count includes packets received but dropped
	 * due to running out of buffer space, and to keep from confusing
	 * applications that, for example, compute packet drop percentages,
	 * we also make it count packets dropped by "bufmod" (otherwise we
	 * might run the risk of the packet drop count being bigger than
	 * the received-packet count).
	 *
	 * "ps_drop" counts packets dropped by "bufmod" because of
	 * flow control requirements or resource exhaustion; it doesn't
	 * count packets dropped by the interface driver, or packets
	 * dropped upstream.  As filtering is done in userland, it counts
	 * packets regardless of whether they would've passed the filter.
	 *
	 * These statistics don't include packets not yet read from
	 * the kernel by libpcap, but they may include packets not
	 * yet read from libpcap by the application.
	 */
	*ps = pd->stat;

	/*
	 * Add in the drop count, as per the above comment.
	 */
	ps->ps_recv += ps->ps_drop;
	return (0);
}