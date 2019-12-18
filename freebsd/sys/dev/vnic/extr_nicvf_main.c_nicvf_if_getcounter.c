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
typedef  int /*<<< orphan*/  uint64_t ;
struct nicvf_hw_stats {int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  tx_bytes_ok; int /*<<< orphan*/  rx_bytes; } ;
struct nicvf_drv_stats {int /*<<< orphan*/  tx_drops; int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  tx_frames_ok; int /*<<< orphan*/  rx_frames_ok; } ;
struct nicvf {struct nicvf_drv_stats drv_stats; struct nicvf_hw_stats hw_stats; } ;
struct ifnet {int dummy; } ;
typedef  int ift_counter ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 135 
#define  IFCOUNTER_IBYTES 134 
#define  IFCOUNTER_IMCASTS 133 
#define  IFCOUNTER_IPACKETS 132 
#define  IFCOUNTER_IQDROPS 131 
#define  IFCOUNTER_OBYTES 130 
#define  IFCOUNTER_OPACKETS 129 
#define  IFCOUNTER_OQDROPS 128 
 int /*<<< orphan*/  if_get_counter_default (struct ifnet*,int) ; 
 struct nicvf* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static uint64_t
nicvf_if_getcounter(struct ifnet *ifp, ift_counter cnt)
{
	struct nicvf *nic;
	struct nicvf_hw_stats *hw_stats;
	struct nicvf_drv_stats *drv_stats;

	nic = if_getsoftc(ifp);
	hw_stats = &nic->hw_stats;
	drv_stats = &nic->drv_stats;

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		return (drv_stats->rx_frames_ok);
	case IFCOUNTER_OPACKETS:
		return (drv_stats->tx_frames_ok);
	case IFCOUNTER_IBYTES:
		return (hw_stats->rx_bytes);
	case IFCOUNTER_OBYTES:
		return (hw_stats->tx_bytes_ok);
	case IFCOUNTER_IMCASTS:
		return (hw_stats->rx_mcast_frames);
	case IFCOUNTER_COLLISIONS:
		return (0);
	case IFCOUNTER_IQDROPS:
		return (drv_stats->rx_drops);
	case IFCOUNTER_OQDROPS:
		return (drv_stats->tx_drops);
	default:
		return (if_get_counter_default(ifp, cnt));
	}

}