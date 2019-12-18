#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ds_sbdrops; scalar_t__ ds_ifdrops; } ;
struct TYPE_5__ {scalar_t__ ss_sbdrops; scalar_t__ ss_ifdrops; } ;
struct rawstats {TYPE_2__ rs_drain; TYPE_1__ rs_snoop; } ;
struct pcap_stat {scalar_t__ ps_drop; } ;
struct pcap_snoop {struct pcap_stat stat; } ;
struct TYPE_7__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; struct pcap_snoop* priv; } ;
typedef  TYPE_3__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCRAWSTATS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct rawstats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcap_stats_snoop(pcap_t *p, struct pcap_stat *ps)
{
	struct pcap_snoop *psn = p->priv;
	register struct rawstats *rs;
	struct rawstats rawstats;

	rs = &rawstats;
	memset(rs, 0, sizeof(*rs));
	if (ioctl(p->fd, SIOCRAWSTATS, (char *)rs) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, sizeof(p->errbuf),
		    errno, "SIOCRAWSTATS");
		return (-1);
	}

	/*
	 * "ifdrops" are those dropped by the network interface
	 * due to resource shortages or hardware errors.
	 *
	 * "sbdrops" are those dropped due to socket buffer limits.
	 *
	 * As filter is done in userland, "sbdrops" counts packets
	 * regardless of whether they would've passed the filter.
	 *
	 * XXX - does this count *all* Snoop or Drain sockets,
	 * rather than just this socket?  If not, why does it have
	 * both Snoop and Drain statistics?
	 */
	psn->stat.ps_drop =
	    rs->rs_snoop.ss_ifdrops + rs->rs_snoop.ss_sbdrops +
	    rs->rs_drain.ds_ifdrops + rs->rs_drain.ds_sbdrops;

	/*
	 * "ps_recv" counts only packets that passed the filter.
	 * As filtering is done in userland, this does not include
	 * packets dropped because we ran out of buffer space.
	 */
	*ps = psn->stat;
	return (0);
}