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
struct ena_hw_stats {int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct ena_adapter {struct ena_hw_stats hw_stats; } ;
typedef  int ift_counter ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
#define  IFCOUNTER_IBYTES 132 
#define  IFCOUNTER_IPACKETS 131 
#define  IFCOUNTER_IQDROPS 130 
#define  IFCOUNTER_OBYTES 129 
#define  IFCOUNTER_OPACKETS 128 
 int /*<<< orphan*/  counter_u64_fetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_get_counter_default (int /*<<< orphan*/ ,int) ; 
 struct ena_adapter* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
ena_get_counter(if_t ifp, ift_counter cnt)
{
	struct ena_adapter *adapter;
	struct ena_hw_stats *stats;

	adapter = if_getsoftc(ifp);
	stats = &adapter->hw_stats;

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		return (counter_u64_fetch(stats->rx_packets));
	case IFCOUNTER_OPACKETS:
		return (counter_u64_fetch(stats->tx_packets));
	case IFCOUNTER_IBYTES:
		return (counter_u64_fetch(stats->rx_bytes));
	case IFCOUNTER_OBYTES:
		return (counter_u64_fetch(stats->tx_bytes));
	case IFCOUNTER_IQDROPS:
		return (counter_u64_fetch(stats->rx_drops));
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}