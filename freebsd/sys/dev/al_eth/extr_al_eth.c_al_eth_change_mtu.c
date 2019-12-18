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
struct al_eth_adapter {int /*<<< orphan*/  hal_adapter; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_MIN_FRAME_LEN ; 
 int ETHER_CRC_LEN ; 
 int ETHER_HDR_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int /*<<< orphan*/  al_eth_req_rx_buff_size (struct al_eth_adapter*,int) ; 
 int /*<<< orphan*/  al_eth_rx_pkt_limit_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_eth_tso_mss_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
al_eth_change_mtu(struct al_eth_adapter *adapter, int new_mtu)
{
	int max_frame = new_mtu + ETHER_HDR_LEN + ETHER_CRC_LEN +
	    ETHER_VLAN_ENCAP_LEN;

	al_eth_req_rx_buff_size(adapter, new_mtu);

	device_printf_dbg(adapter->dev, "set MTU to %d\n", new_mtu);
	al_eth_rx_pkt_limit_config(&adapter->hal_adapter,
	    AL_ETH_MIN_FRAME_LEN, max_frame);

	al_eth_tso_mss_config(&adapter->hal_adapter, 0, new_mtu - 100);

	return (0);
}