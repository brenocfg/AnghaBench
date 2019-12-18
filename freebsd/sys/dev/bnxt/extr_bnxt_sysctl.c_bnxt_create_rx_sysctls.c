#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct ctx_hw_stats {int /*<<< orphan*/  tpa_aborts; int /*<<< orphan*/  tpa_events; int /*<<< orphan*/  tpa_bytes; int /*<<< orphan*/  tpa_pkts; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_ucast_bytes; int /*<<< orphan*/  rx_drop_pkts; int /*<<< orphan*/  rx_discard_pkts; int /*<<< orphan*/  rx_bcast_pkts; int /*<<< orphan*/  rx_mcast_pkts; int /*<<< orphan*/  rx_ucast_pkts; } ;
struct TYPE_2__ {scalar_t__ idi_vaddr; } ;
struct bnxt_softc {int /*<<< orphan*/  hw_stats; struct sysctl_oid* hw_stats_oid; TYPE_1__ rx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int
bnxt_create_rx_sysctls(struct bnxt_softc *softc, int rxr)
{
	struct sysctl_oid *oid;
	struct ctx_hw_stats *rx_stats = (void *)softc->rx_stats.idi_vaddr;
	char	name[32];
	char	desc[64];

	sprintf(name, "rxq%d", rxr);
	sprintf(desc, "receive queue %d", rxr);
	oid = SYSCTL_ADD_NODE(&softc->hw_stats,
	    SYSCTL_CHILDREN(softc->hw_stats_oid), OID_AUTO, name, CTLFLAG_RD, 0,
	    desc);
	if (!oid)
		return ENOMEM;

	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "ucast_pkts", CTLFLAG_RD, &rx_stats[rxr].rx_ucast_pkts,
	    "unicast packets received");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "mcast_pkts", CTLFLAG_RD, &rx_stats[rxr].rx_mcast_pkts,
	    "multicast packets received");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "bcast_pkts", CTLFLAG_RD, &rx_stats[rxr].rx_bcast_pkts,
	    "broadcast packets received");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "discard_pkts", CTLFLAG_RD,
	    &rx_stats[rxr].rx_discard_pkts, "discarded receive packets");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "drop_pkts", CTLFLAG_RD, &rx_stats[rxr].rx_drop_pkts,
	    "dropped receive packets");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "ucast_bytes", CTLFLAG_RD, &rx_stats[rxr].rx_ucast_bytes,
	    "unicast bytes received");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "mcast_bytes", CTLFLAG_RD, &rx_stats[rxr].rx_mcast_bytes,
	    "multicast bytes received");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "bcast_bytes", CTLFLAG_RD, &rx_stats[rxr].rx_bcast_bytes,
	    "broadcast bytes received");

	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "tpa_pkts", CTLFLAG_RD, &rx_stats[rxr].tpa_pkts,
	    "TPA packets");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "tpa_bytes", CTLFLAG_RD, &rx_stats[rxr].tpa_bytes,
	    "TPA bytes");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "tpa_events", CTLFLAG_RD, &rx_stats[rxr].tpa_events,
	    "TPA events");
	SYSCTL_ADD_QUAD(&softc->hw_stats, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "tpa_aborts", CTLFLAG_RD, &rx_stats[rxr].tpa_aborts,
	    "TPA aborts");

	return 0;
}