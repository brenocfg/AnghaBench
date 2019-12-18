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
typedef  int uint32_t ;
struct al_eth_fwd_mac_table_entry {scalar_t__ filter; int udma_mask; int qid; scalar_t__ rx_valid; int tx_target; scalar_t__ tx_valid; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int EC_FWD_MAC_CTRL_RX_VALID ; 
 int EC_FWD_MAC_CTRL_RX_VAL_DROP ; 
 int EC_FWD_MAC_CTRL_RX_VAL_QID_MASK ; 
 int EC_FWD_MAC_CTRL_RX_VAL_QID_SHIFT ; 
 int EC_FWD_MAC_CTRL_RX_VAL_UDMA_MASK ; 
 int EC_FWD_MAC_CTRL_RX_VAL_UDMA_SHIFT ; 
 int EC_FWD_MAC_CTRL_TX_VALID ; 
 int EC_FWD_MAC_CTRL_TX_VAL_MASK ; 
 int EC_FWD_MAC_CTRL_TX_VAL_SHIFT ; 

__attribute__((used)) static uint32_t	al_eth_fwd_mac_table_entry_to_val(struct al_eth_fwd_mac_table_entry *entry)
{
	uint32_t val = 0;

	val |= (entry->filter == AL_TRUE) ? EC_FWD_MAC_CTRL_RX_VAL_DROP : 0;
	val |= ((entry->udma_mask << EC_FWD_MAC_CTRL_RX_VAL_UDMA_SHIFT) &
					EC_FWD_MAC_CTRL_RX_VAL_UDMA_MASK);

	val |= ((entry->qid << EC_FWD_MAC_CTRL_RX_VAL_QID_SHIFT) &
					EC_FWD_MAC_CTRL_RX_VAL_QID_MASK);

	val |= (entry->rx_valid == AL_TRUE) ? EC_FWD_MAC_CTRL_RX_VALID : 0;

	val |= ((entry->tx_target << EC_FWD_MAC_CTRL_TX_VAL_SHIFT) &
					EC_FWD_MAC_CTRL_TX_VAL_MASK);

	val |= (entry->tx_valid == AL_TRUE) ? EC_FWD_MAC_CTRL_TX_VALID : 0;

	return val;
}