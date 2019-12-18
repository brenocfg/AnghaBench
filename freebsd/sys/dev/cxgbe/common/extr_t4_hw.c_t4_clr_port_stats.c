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
typedef  int u32 ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int mps_bg_map; } ;

/* Variables and functions */
 unsigned int A_MPS_PORT_STAT_RX_PORT_BYTES_L ; 
 unsigned int A_MPS_PORT_STAT_RX_PORT_LESS_64B_H ; 
 unsigned int A_MPS_PORT_STAT_TX_PORT_BYTES_L ; 
 unsigned int A_MPS_PORT_STAT_TX_PORT_PPP7_H ; 
 int A_MPS_STAT_RX_BG_0_MAC_DROP_FRAME_L ; 
 int A_MPS_STAT_RX_BG_0_MAC_TRUNC_FRAME_L ; 
 int PORT_BASE (int) ; 
 int T5_PORT_BASE (int) ; 
 TYPE_1__* adap2pinfo (struct adapter*,int) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int /*<<< orphan*/ ) ; 

void t4_clr_port_stats(struct adapter *adap, int idx)
{
	unsigned int i;
	u32 bgmap = adap2pinfo(adap, idx)->mps_bg_map;
	u32 port_base_addr;

	if (is_t4(adap))
		port_base_addr = PORT_BASE(idx);
	else
		port_base_addr = T5_PORT_BASE(idx);

	for (i = A_MPS_PORT_STAT_TX_PORT_BYTES_L;
			i <= A_MPS_PORT_STAT_TX_PORT_PPP7_H; i += 8)
		t4_write_reg(adap, port_base_addr + i, 0);
	for (i = A_MPS_PORT_STAT_RX_PORT_BYTES_L;
			i <= A_MPS_PORT_STAT_RX_PORT_LESS_64B_H; i += 8)
		t4_write_reg(adap, port_base_addr + i, 0);
	for (i = 0; i < 4; i++)
		if (bgmap & (1 << i)) {
			t4_write_reg(adap,
			A_MPS_STAT_RX_BG_0_MAC_DROP_FRAME_L + i * 8, 0);
			t4_write_reg(adap,
			A_MPS_STAT_RX_BG_0_MAC_TRUNC_FRAME_L + i * 8, 0);
		}
}