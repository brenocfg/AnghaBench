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
struct cmac {scalar_t__ offset; } ;
struct port_info {struct cmac mac; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 scalar_t__ A_XGM_INT_STATUS ; 
 scalar_t__ A_XGM_RX_CTRL ; 
 int F_LINKFAULTCHANGE ; 
 int /*<<< orphan*/  F_RXEN ; 
 struct port_info* adap2pinfo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t3_gate_rx_traffic (struct cmac*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_open_rx_traffic (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_read_reg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_xgm_intr_enable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int t3_detect_link_fault(adapter_t *adapter, int port_id)
{
	struct port_info *pi = adap2pinfo(adapter, port_id);
	struct cmac *mac = &pi->mac;
	uint32_t rx_cfg, rx_hash_high, rx_hash_low;
	int link_fault;

	/* stop rx */
	t3_gate_rx_traffic(mac, &rx_cfg, &rx_hash_high, &rx_hash_low);
	t3_write_reg(adapter, A_XGM_RX_CTRL + mac->offset, 0);

	/* clear status and make sure intr is enabled */
	(void) t3_read_reg(adapter, A_XGM_INT_STATUS + mac->offset);
	t3_xgm_intr_enable(adapter, port_id);

	/* restart rx */
	t3_write_reg(adapter, A_XGM_RX_CTRL + mac->offset, F_RXEN);
	t3_open_rx_traffic(mac, rx_cfg, rx_hash_high, rx_hash_low);

	link_fault = t3_read_reg(adapter, A_XGM_INT_STATUS + mac->offset);
	return (link_fault & F_LINKFAULTCHANGE ? 1 : 0);
}