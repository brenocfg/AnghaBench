#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tp_params {int dummy; } ;
struct TYPE_8__ {scalar_t__ rev; int nports; } ;
struct TYPE_9__ {TYPE_1__ params; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_DACK_CONFIG ; 
 int /*<<< orphan*/  A_TP_EGRESS_CONFIG ; 
 int /*<<< orphan*/  A_TP_GLOBAL_CONFIG ; 
 int /*<<< orphan*/  A_TP_INGRESS_CONFIG ; 
 int /*<<< orphan*/  A_TP_INTF_FROM_TX_PKT ; 
 int /*<<< orphan*/  A_TP_IN_CONFIG ; 
 int /*<<< orphan*/  A_TP_MAC_MATCH_MAP0 ; 
 int /*<<< orphan*/  A_TP_MAC_MATCH_MAP1 ; 
 int /*<<< orphan*/  A_TP_MOD_CHANNEL_WEIGHT ; 
 int /*<<< orphan*/  A_TP_MOD_RATE_LIMIT ; 
 int /*<<< orphan*/  A_TP_PARA_REG3 ; 
 int /*<<< orphan*/  A_TP_PARA_REG4 ; 
 int /*<<< orphan*/  A_TP_PARA_REG6 ; 
 int /*<<< orphan*/  A_TP_PC_CONFIG ; 
 int /*<<< orphan*/  A_TP_PC_CONFIG2 ; 
 int /*<<< orphan*/  A_TP_PREAMBLE_LSB ; 
 int /*<<< orphan*/  A_TP_PREAMBLE_MSB ; 
 int /*<<< orphan*/  A_TP_PROXY_FLOW_CNTL ; 
 int /*<<< orphan*/  A_TP_QOS_RX_MAP_MODE ; 
 int /*<<< orphan*/  A_TP_TCP_OPTIONS ; 
 int /*<<< orphan*/  A_TP_TX_MOD_QUEUE_WEIGHT0 ; 
 int /*<<< orphan*/  A_TP_TX_MOD_QUEUE_WEIGHT1 ; 
 int /*<<< orphan*/  A_TP_TX_RESOURCE_LIMIT ; 
 int /*<<< orphan*/  A_TP_VLAN_PRI_MAP ; 
 int F_AUTOCAREFUL ; 
 int F_AUTOENABLE ; 
 int F_CHDRAFULL ; 
 int F_DISBLEDAPARBIT0 ; 
 int F_ENABLEARPMISS ; 
 int F_ENABLEEPCMDAFULL ; 
 int F_ENABLEESND ; 
 int F_ENABLEEXTRACT ; 
 int F_ENABLEEXTRACTIONSFD ; 
 int F_ENABLEINSERTION ; 
 int F_ENABLEINSERTIONSFD ; 
 int F_ENABLEIPV6RSS ; 
 int F_ENABLENONOFDTNLSYN ; 
 int F_ENABLEOCSPIFULL ; 
 int F_ENABLERXPORTFROMADDR ; 
 int F_ENABLETXPORTFROMDA ; 
 int F_ENABLETXPORTFROMDA2 ; 
 int F_HEARBEATDACK ; 
 int F_INTFFROMTXPKT ; 
 int F_IPCHECKSUMOFFLOAD ; 
 int F_IPV6ENABLE ; 
 int F_LOCKTID ; 
 int F_MTUENABLE ; 
 int F_NICMODE ; 
 int F_PATHMTU ; 
 int F_REWRITEFORCETOSIZE ; 
 int F_RXCONGESTIONMODE ; 
 int F_RXFBARBPRIO ; 
 int F_T3A_ENABLEESND ; 
 int F_TCPCHECKSUMOFFLOAD ; 
 int F_TXCONGESTIONMODE ; 
 int F_TXDEFERENABLE ; 
 int F_TXFBARBPRIO ; 
 int F_TXPACEAUTO ; 
 int F_TXPACEAUTOSTRICT ; 
 int F_TXPACEFIXED ; 
 int F_TXPACINGENABLE ; 
 int F_UDPCHECKSUMOFFLOAD ; 
 int /*<<< orphan*/  M_RXMAPMODE ; 
 int M_TABLELATENCYDELTA ; 
 scalar_t__ T3_REV_C ; 
 int V_AUTOSTATE1 (int /*<<< orphan*/ ) ; 
 int V_AUTOSTATE2 (int) ; 
 int V_AUTOSTATE3 (int) ; 
 int V_BITPOS0 (int) ; 
 int V_BITPOS1 (int) ; 
 int V_BITPOS2 (int) ; 
 int V_BITPOS3 (int) ; 
 int V_BYTETHRESHOLD (int) ; 
 int V_DACK_MODE (int) ; 
 int V_IPTTL (int) ; 
 int V_MSSTHRESHOLD (int) ; 
 int V_MTUDEFAULT (int) ; 
 int /*<<< orphan*/  V_RXMAPMODE (int /*<<< orphan*/ ) ; 
 int V_SACKMODE (int) ; 
 int V_SACKRX (int) ; 
 int V_TABLELATENCYDELTA (int) ; 
 int V_TIMESTAMPSMODE (int) ; 
 int V_WINDOWSCALEMODE (int) ; 
 int /*<<< orphan*/  t3_set_reg_field (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tp_wr_bits_indirect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_wr_indirect (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tp_config(adapter_t *adap, const struct tp_params *p)
{
	t3_write_reg(adap, A_TP_GLOBAL_CONFIG, F_TXPACINGENABLE | F_PATHMTU |
		     F_IPCHECKSUMOFFLOAD | F_UDPCHECKSUMOFFLOAD |
		     F_TCPCHECKSUMOFFLOAD | V_IPTTL(64));
	t3_write_reg(adap, A_TP_TCP_OPTIONS, V_MTUDEFAULT(576) |
		     F_MTUENABLE | V_WINDOWSCALEMODE(1) |
		     V_TIMESTAMPSMODE(1) | V_SACKMODE(1) | V_SACKRX(1));
	t3_write_reg(adap, A_TP_DACK_CONFIG, V_AUTOSTATE3(1) |
		     V_AUTOSTATE2(1) | V_AUTOSTATE1(0) |
		     V_BYTETHRESHOLD(26880) | V_MSSTHRESHOLD(2) |
		     F_AUTOCAREFUL | F_AUTOENABLE | V_DACK_MODE(1));
	t3_set_reg_field(adap, A_TP_IN_CONFIG, F_RXFBARBPRIO | F_TXFBARBPRIO,
			 F_IPV6ENABLE | F_NICMODE);
	t3_write_reg(adap, A_TP_TX_RESOURCE_LIMIT, 0x18141814);
	t3_write_reg(adap, A_TP_PARA_REG4, 0x5050105);
	t3_set_reg_field(adap, A_TP_PARA_REG6, 0,
			 adap->params.rev > 0 ? F_ENABLEESND :
			 			F_T3A_ENABLEESND);
	t3_set_reg_field(adap, A_TP_PC_CONFIG,
			 F_ENABLEEPCMDAFULL,
			 F_ENABLEOCSPIFULL |F_TXDEFERENABLE | F_HEARBEATDACK |
			 F_TXCONGESTIONMODE | F_RXCONGESTIONMODE);
	t3_set_reg_field(adap, A_TP_PC_CONFIG2, F_CHDRAFULL,
			 F_ENABLEIPV6RSS | F_ENABLENONOFDTNLSYN |
			 F_ENABLEARPMISS | F_DISBLEDAPARBIT0);
	t3_write_reg(adap, A_TP_PROXY_FLOW_CNTL, 1080);
	t3_write_reg(adap, A_TP_PROXY_FLOW_CNTL, 1000);

	if (adap->params.rev > 0) {
		tp_wr_indirect(adap, A_TP_EGRESS_CONFIG, F_REWRITEFORCETOSIZE);
		t3_set_reg_field(adap, A_TP_PARA_REG3, 0,
				 F_TXPACEAUTO | F_TXPACEAUTOSTRICT);
		t3_set_reg_field(adap, A_TP_PC_CONFIG, F_LOCKTID, F_LOCKTID);
		tp_wr_indirect(adap, A_TP_VLAN_PRI_MAP, 0xfa50);
		tp_wr_indirect(adap, A_TP_MAC_MATCH_MAP0, 0xfac688);
		tp_wr_indirect(adap, A_TP_MAC_MATCH_MAP1, 0xfac688);
	} else
		t3_set_reg_field(adap, A_TP_PARA_REG3, 0, F_TXPACEFIXED);

	if (adap->params.rev == T3_REV_C)
		t3_set_reg_field(adap, A_TP_PC_CONFIG,
				 V_TABLELATENCYDELTA(M_TABLELATENCYDELTA),
				 V_TABLELATENCYDELTA(4));

	t3_write_reg(adap, A_TP_TX_MOD_QUEUE_WEIGHT1, 0);
	t3_write_reg(adap, A_TP_TX_MOD_QUEUE_WEIGHT0, 0);
	t3_write_reg(adap, A_TP_MOD_CHANNEL_WEIGHT, 0);
	t3_write_reg(adap, A_TP_MOD_RATE_LIMIT, 0xf2200000);

	if (adap->params.nports > 2) {
		t3_set_reg_field(adap, A_TP_PC_CONFIG2, 0,
				 F_ENABLETXPORTFROMDA2 | F_ENABLETXPORTFROMDA |
				 F_ENABLERXPORTFROMADDR);
		tp_wr_bits_indirect(adap, A_TP_QOS_RX_MAP_MODE,
				    V_RXMAPMODE(M_RXMAPMODE), 0);
		tp_wr_indirect(adap, A_TP_INGRESS_CONFIG, V_BITPOS0(48) |
			       V_BITPOS1(49) | V_BITPOS2(50) | V_BITPOS3(51) |
			       F_ENABLEEXTRACT | F_ENABLEEXTRACTIONSFD |
			       F_ENABLEINSERTION | F_ENABLEINSERTIONSFD);
		tp_wr_indirect(adap, A_TP_PREAMBLE_MSB, 0xfb000000);
		tp_wr_indirect(adap, A_TP_PREAMBLE_LSB, 0xd5);
		tp_wr_indirect(adap, A_TP_INTF_FROM_TX_PKT, F_INTFFROMTXPKT);
	}
}