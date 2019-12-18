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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_eth_fwd_ctrl_table_index {scalar_t__ vlan_table_out; scalar_t__ tunnel_exist; scalar_t__ vlan_exist; scalar_t__ mac_table_match; scalar_t__ protocol_id; scalar_t__ mac_type; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE_ANY ; 
 scalar_t__ AL_ETH_FWD_CTRL_IDX_MAC_TABLE_ANY ; 
 scalar_t__ AL_ETH_FWD_CTRL_IDX_TUNNEL_ANY ; 
 scalar_t__ AL_ETH_FWD_CTRL_IDX_VLAN_ANY ; 
 scalar_t__ AL_ETH_FWD_CTRL_IDX_VLAN_TABLE_OUT_ANY ; 
 scalar_t__ AL_ETH_PROTO_ID_ANY ; 
 int /*<<< orphan*/  AL_FIELD_MASK (int,int) ; 
 scalar_t__ AL_REG_BIT_GET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AL_REG_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int al_eth_ctrl_index_match(struct al_eth_fwd_ctrl_table_index *index, uint32_t i) {
	if ((index->vlan_table_out != AL_ETH_FWD_CTRL_IDX_VLAN_TABLE_OUT_ANY)
		&& (index->vlan_table_out != AL_REG_BIT_GET(i, 0)))
		return 0;
	if ((index->tunnel_exist != AL_ETH_FWD_CTRL_IDX_TUNNEL_ANY)
		&& (index->tunnel_exist != AL_REG_BIT_GET(i, 1)))
		return 0;
	if ((index->vlan_exist != AL_ETH_FWD_CTRL_IDX_VLAN_ANY)
		&& (index->vlan_exist != AL_REG_BIT_GET(i, 2)))
		return 0;
	if ((index->mac_table_match != AL_ETH_FWD_CTRL_IDX_MAC_TABLE_ANY)
		&& (index->mac_table_match != AL_REG_BIT_GET(i, 3)))
		return 0;
	if ((index->protocol_id != AL_ETH_PROTO_ID_ANY)
		&& (index->protocol_id != AL_REG_FIELD_GET(i, AL_FIELD_MASK(8,4),4)))
		return 0;
	if ((index->mac_type != AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE_ANY)
		&& (index->mac_type != AL_REG_FIELD_GET(i, AL_FIELD_MASK(10,9),9)))
		return 0;
	return 1;
}