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
struct pcap_pf {scalar_t__ OrigMissed; scalar_t__ TotMissed; int /*<<< orphan*/  TotDrops; int /*<<< orphan*/  TotAccepted; } ;
struct TYPE_3__ {struct pcap_pf* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */

__attribute__((used)) static int
pcap_stats_pf(pcap_t *p, struct pcap_stat *ps)
{
	struct pcap_pf *pf = p->priv;

	/*
	 * If packet filtering is being done in the kernel:
	 *
	 *	"ps_recv" counts only packets that passed the filter.
	 *	This does not include packets dropped because we
	 *	ran out of buffer space.  (XXX - perhaps it should,
	 *	by adding "ps_drop" to "ps_recv", for compatibility
	 *	with some other platforms.  On the other hand, on
	 *	some platforms "ps_recv" counts only packets that
	 *	passed the filter, and on others it counts packets
	 *	that didn't pass the filter....)
	 *
	 *	"ps_drop" counts packets that passed the kernel filter
	 *	(if any) but were dropped because the input queue was
	 *	full.
	 *
	 *	"ps_ifdrop" counts packets dropped by the network
	 *	inteface (regardless of whether they would have passed
	 *	the input filter, of course).
	 *
	 * If packet filtering is not being done in the kernel:
	 *
	 *	"ps_recv" counts only packets that passed the filter.
	 *
	 *	"ps_drop" counts packets that were dropped because the
	 *	input queue was full, regardless of whether they passed
	 *	the userland filter.
	 *
	 *	"ps_ifdrop" counts packets dropped by the network
	 *	inteface (regardless of whether they would have passed
	 *	the input filter, of course).
	 *
	 * These statistics don't include packets not yet read from
	 * the kernel by libpcap, but they may include packets not
	 * yet read from libpcap by the application.
	 */
	ps->ps_recv = pf->TotAccepted;
	ps->ps_drop = pf->TotDrops;
	ps->ps_ifdrop = pf->TotMissed - pf->OrigMissed;
	return (0);
}