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
typedef  scalar_t__ uint64_t ;
struct ifnet {int dummy; } ;
struct al_eth_mac_stats {scalar_t__ ifOutErrors; scalar_t__ aAlignmentErrors; scalar_t__ aFrameCheckSequenceErrors; scalar_t__ etherStatsOversizePkts; scalar_t__ etherStatsJabbers; scalar_t__ etherStatsFragments; scalar_t__ etherStatsUndersizePkts; scalar_t__ ifInErrors; scalar_t__ etherStatsDropEvents; scalar_t__ ifOutMulticastPkts; scalar_t__ ifInMulticastPkts; scalar_t__ aOctetsTransmittedOK; scalar_t__ aOctetsReceivedOK; scalar_t__ aFramesTransmittedOK; scalar_t__ aFramesReceivedOK; } ;
struct al_eth_adapter {struct al_eth_mac_stats mac_stats; } ;
typedef  int ift_counter ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 137 
#define  IFCOUNTER_IBYTES 136 
#define  IFCOUNTER_IERRORS 135 
#define  IFCOUNTER_IMCASTS 134 
#define  IFCOUNTER_IPACKETS 133 
#define  IFCOUNTER_IQDROPS 132 
#define  IFCOUNTER_OBYTES 131 
#define  IFCOUNTER_OERRORS 130 
#define  IFCOUNTER_OMCASTS 129 
#define  IFCOUNTER_OPACKETS 128 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 struct al_eth_adapter* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static uint64_t
al_get_counter(struct ifnet *ifp, ift_counter cnt)
{
	struct al_eth_adapter *adapter;
	struct al_eth_mac_stats *mac_stats;
	uint64_t rv;

	adapter = if_getsoftc(ifp);
	mac_stats = &adapter->mac_stats;

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		return (mac_stats->aFramesReceivedOK); /* including pause frames */
	case IFCOUNTER_OPACKETS:
		return (mac_stats->aFramesTransmittedOK);
	case IFCOUNTER_IBYTES:
		return (mac_stats->aOctetsReceivedOK);
	case IFCOUNTER_OBYTES:
		return (mac_stats->aOctetsTransmittedOK);
	case IFCOUNTER_IMCASTS:
		return (mac_stats->ifInMulticastPkts);
	case IFCOUNTER_OMCASTS:
		return (mac_stats->ifOutMulticastPkts);
	case IFCOUNTER_COLLISIONS:
		return (0);
	case IFCOUNTER_IQDROPS:
		return (mac_stats->etherStatsDropEvents);
	case IFCOUNTER_IERRORS:
		rv = mac_stats->ifInErrors +
		    mac_stats->etherStatsUndersizePkts + /* good but short */
		    mac_stats->etherStatsFragments + /* short and bad*/
		    mac_stats->etherStatsJabbers + /* with crc errors */
		    mac_stats->etherStatsOversizePkts +
		    mac_stats->aFrameCheckSequenceErrors +
		    mac_stats->aAlignmentErrors;
		return (rv);
	case IFCOUNTER_OERRORS:
		return (mac_stats->ifOutErrors);
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}