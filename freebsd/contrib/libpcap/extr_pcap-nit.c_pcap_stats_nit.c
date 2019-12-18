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
struct pcap_stat {int dummy; } ;
struct pcap_nit {struct pcap_stat stat; } ;
struct TYPE_3__ {struct pcap_nit* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */

__attribute__((used)) static int
pcap_stats_nit(pcap_t *p, struct pcap_stat *ps)
{
	struct pcap_nit *pn = p->priv;

	/*
	 * "ps_recv" counts packets handed to the filter, not packets
	 * that passed the filter.  As filtering is done in userland,
	 * this does not include packets dropped because we ran out
	 * of buffer space.
	 *
	 * "ps_drop" presumably counts packets dropped by the socket
	 * because of flow control requirements or resource exhaustion;
	 * it doesn't count packets dropped by the interface driver.
	 * As filtering is done in userland, it counts packets regardless
	 * of whether they would've passed the filter.
	 *
	 * These statistics don't include packets not yet read from the
	 * kernel by libpcap or packets not yet read from libpcap by the
	 * application.
	 */
	*ps = pn->stat;
	return (0);
}