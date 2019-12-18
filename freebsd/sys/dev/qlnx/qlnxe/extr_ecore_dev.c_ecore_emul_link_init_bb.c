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
typedef  int u8 ;
typedef  int u64 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int port_id; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XLMAC_CTRL ; 
 int /*<<< orphan*/  XLMAC_MODE ; 
 int /*<<< orphan*/  XLMAC_PAUSE_CTRL ; 
 int /*<<< orphan*/  XLMAC_PFC_CTRL ; 
 int /*<<< orphan*/  XLMAC_RX_MAX_SIZE ; 
 int /*<<< orphan*/  XLMAC_TX_CTRL ; 
 int /*<<< orphan*/  XLPORT_ENABLE_REG ; 
 int /*<<< orphan*/  XLPORT_FLOW_CONTROL_CONFIG ; 
 int /*<<< orphan*/  XLPORT_MAC_CONTROL ; 
 int /*<<< orphan*/  XLPORT_MODE_REG ; 
 int /*<<< orphan*/  ecore_wr_nw_port (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void ecore_emul_link_init_bb(struct ecore_hwfn *p_hwfn,
				    struct ecore_ptt *p_ptt)
{
	u8 loopback = 0, port = p_hwfn->port_id * 2;

	DP_INFO(p_hwfn->p_dev, "Configurating Emulation Link %02x\n", port);

	ecore_wr_nw_port(p_hwfn, p_ptt, XLPORT_MODE_REG,
			 (0x4 << 4) | 0x4, 1, port); /* XLPORT MAC MODE */ /* 0 Quad, 4 Single... */
	ecore_wr_nw_port(p_hwfn, p_ptt, XLPORT_MAC_CONTROL, 0, 1, port);
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_CTRL,
			 0x40, 0, port); /*XLMAC: SOFT RESET */
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_MODE,
			 0x40, 0, port); /*XLMAC: Port Speed >= 10Gbps */
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_RX_MAX_SIZE,
			 0x3fff, 0, port); /* XLMAC: Max Size */
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_TX_CTRL,
			 0x01000000800ULL | (0xa << 12) | ((u64)1 << 38),
			 0, port);
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_PAUSE_CTRL,
			 0x7c000, 0, port);
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_PFC_CTRL,
			 0x30ffffc000ULL, 0, port);
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_CTRL, 0x3 | (loopback << 2),
			 0, port); /* XLMAC: TX_EN, RX_EN */
	ecore_wr_nw_port(p_hwfn, p_ptt, XLMAC_CTRL, 0x1003 | (loopback << 2),
			 0, port); /* XLMAC: TX_EN, RX_EN, SW_LINK_STATUS */
	ecore_wr_nw_port(p_hwfn, p_ptt, XLPORT_FLOW_CONTROL_CONFIG,
			 1, 0, port); /* Enabled Parallel PFC interface */
	ecore_wr_nw_port(p_hwfn, p_ptt, XLPORT_ENABLE_REG,
			 0xf, 1, port); /* XLPORT port enable */
}