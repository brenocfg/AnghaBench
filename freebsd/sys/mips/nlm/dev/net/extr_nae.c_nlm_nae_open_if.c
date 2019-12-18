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
typedef  int uint32_t ;

/* Variables and functions */
#define  ILC 130 
 int NETIOR_XGMAC_STATS_CLR_POS ; 
#define  SGMIIC 129 
 int SGMII_MAC_CONF1 (int,int) ; 
 int SGMII_MAC_CONF2 (int,int) ; 
 int SGMII_NET_IFACE_CTRL (int,int) ; 
 int SGMII_NET_IFACE_CTRL3 (int,int) ; 
#define  XAUIC 128 
 int XAUI_NETIOR_XGMAC_CTRL1 (int) ; 
 int /*<<< orphan*/  nlm_nae_init_egress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_nae_init_ingress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_nae_set_ior_credit (int /*<<< orphan*/ ,int,int) ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int,int) ; 

int
nlm_nae_open_if(uint64_t nae_base, int nblock, int port_type,
    int port, uint32_t desc_size)
{
	uint32_t netwk_inf;
	uint32_t mac_cfg1, netior_ctrl3;
	int iface, iface_ctrl_reg, iface_ctrl3_reg, conf1_reg, conf2_reg;

	switch (port_type) {
	case XAUIC:
		netwk_inf = nlm_read_nae_reg(nae_base,
		    XAUI_NETIOR_XGMAC_CTRL1(nblock));
		netwk_inf |= (1 << NETIOR_XGMAC_STATS_CLR_POS);
		nlm_write_nae_reg(nae_base,
		    XAUI_NETIOR_XGMAC_CTRL1(nblock), netwk_inf);

		nlm_nae_set_ior_credit(nae_base, 0xf << port, 0xf << port);
		break;

	case ILC:
		nlm_nae_set_ior_credit(nae_base, 0xff << port, 0xff << port);
		break;

	case SGMIIC:
		nlm_nae_set_ior_credit(nae_base, 0x1 << port, 0);

		/*
		 * XXXJC: split this and merge to sgmii.c
		 * some of this is duplicated from there.
		 */
		/* init phy id to access internal PCS */
		iface = port & 0x3;
		iface_ctrl_reg = SGMII_NET_IFACE_CTRL(nblock, iface);
		conf1_reg = SGMII_MAC_CONF1(nblock, iface);
		conf2_reg = SGMII_MAC_CONF2(nblock, iface);

		netwk_inf = nlm_read_nae_reg(nae_base, iface_ctrl_reg);
		netwk_inf &= 0x7ffffff;
		netwk_inf |= (port << 27);
		nlm_write_nae_reg(nae_base, iface_ctrl_reg, netwk_inf);

		/* Sofreset sgmii port - set bit 11 to 0  */
		netwk_inf &= 0xfffff7ff;
		nlm_write_nae_reg(nae_base, iface_ctrl_reg, netwk_inf);

		/* Reset Gmac */
		mac_cfg1 = nlm_read_nae_reg(nae_base, conf1_reg);
		nlm_write_nae_reg(nae_base, conf1_reg,
		    mac_cfg1	|
		    (1U << 31)	|	/* soft reset */
		    (1 << 2)	|	/* rx enable */
		    (1));		/* tx enable */

		/* default to 1G */
		nlm_write_nae_reg(nae_base,
		    conf2_reg,
		    (0x7 << 12)	|	/* interface preamble length */
		    (0x2 << 8)	|	/* interface mode */
		    (0x1 << 2)	|	/* pad crc enable */
		    (0x1));		/* full duplex */

		/* clear gmac reset */
		mac_cfg1 = nlm_read_nae_reg(nae_base, conf1_reg);
		nlm_write_nae_reg(nae_base, conf1_reg, mac_cfg1 & ~(1U << 31));

		/* clear speed debug bit */
		iface_ctrl3_reg = SGMII_NET_IFACE_CTRL3(nblock, iface);
		netior_ctrl3 = nlm_read_nae_reg(nae_base, iface_ctrl3_reg);
		nlm_write_nae_reg(nae_base, iface_ctrl3_reg,
		    netior_ctrl3 & ~(1 << 6));

		/* disable TX, RX for now */
		mac_cfg1 = nlm_read_nae_reg(nae_base, conf1_reg);
		nlm_write_nae_reg(nae_base, conf1_reg, mac_cfg1 & ~(0x5));
		netwk_inf = nlm_read_nae_reg(nae_base, iface_ctrl_reg);
		nlm_write_nae_reg(nae_base, iface_ctrl_reg,
		    netwk_inf & ~(0x1 << 2));

		/* clear stats counters */
		netwk_inf = nlm_read_nae_reg(nae_base, iface_ctrl_reg);
		nlm_write_nae_reg(nae_base, iface_ctrl_reg,
		    netwk_inf | (1 << 15));

		/* enable stats counters */
		netwk_inf = nlm_read_nae_reg(nae_base, iface_ctrl_reg);
		nlm_write_nae_reg(nae_base, iface_ctrl_reg,
		    (netwk_inf & ~(1 << 15)) | (1 << 16));

		/* flow control? */
		mac_cfg1 = nlm_read_nae_reg(nae_base, conf1_reg);
		nlm_write_nae_reg(nae_base, conf1_reg,
		    mac_cfg1 | (0x3 << 4));
		break;
	}

	nlm_nae_init_ingress(nae_base, desc_size);
	nlm_nae_init_egress(nae_base);

	return (0);
}