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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct ixl_sysctl_info {char* member_1; char* member_2; scalar_t__ stat; int /*<<< orphan*/  description; int /*<<< orphan*/  name; int /*<<< orphan*/ * member_0; } ;
struct i40e_eth_stats {int /*<<< orphan*/  tx_broadcast; int /*<<< orphan*/  tx_multicast; int /*<<< orphan*/  tx_unicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_discards; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  rx_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void
ixl_add_sysctls_eth_stats(struct sysctl_ctx_list *ctx,
	struct sysctl_oid_list *child,
	struct i40e_eth_stats *eth_stats)
{
	struct ixl_sysctl_info ctls[] =
	{
		{&eth_stats->rx_bytes, "good_octets_rcvd", "Good Octets Received"},
		{&eth_stats->rx_unicast, "ucast_pkts_rcvd",
			"Unicast Packets Received"},
		{&eth_stats->rx_multicast, "mcast_pkts_rcvd",
			"Multicast Packets Received"},
		{&eth_stats->rx_broadcast, "bcast_pkts_rcvd",
			"Broadcast Packets Received"},
		{&eth_stats->rx_discards, "rx_discards", "Discarded RX packets"},
		{&eth_stats->tx_bytes, "good_octets_txd", "Good Octets Transmitted"},
		{&eth_stats->tx_unicast, "ucast_pkts_txd", "Unicast Packets Transmitted"},
		{&eth_stats->tx_multicast, "mcast_pkts_txd",
			"Multicast Packets Transmitted"},
		{&eth_stats->tx_broadcast, "bcast_pkts_txd",
			"Broadcast Packets Transmitted"},
		// end
		{0,0,0}
	};

	struct ixl_sysctl_info *entry = ctls;
	while (entry->stat != 0)
	{
		SYSCTL_ADD_UQUAD(ctx, child, OID_AUTO, entry->name,
				CTLFLAG_RD, entry->stat,
				entry->description);
		entry++;
	}
}