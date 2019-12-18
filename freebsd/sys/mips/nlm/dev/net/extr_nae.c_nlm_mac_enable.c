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
#define  SGMIIC 129 
 int /*<<< orphan*/  SGMII_MAC_CONF1 (int,int) ; 
 int /*<<< orphan*/  SGMII_NET_IFACE_CTRL (int,int) ; 
#define  XAUIC 128 
 int /*<<< orphan*/  XAUI_CONFIG1 (int) ; 
 int XAUI_CONFIG_RFEN ; 
 int XAUI_CONFIG_TFEN ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_mac_enable(uint64_t nae_base, int nblock, int port_type, int port)
{
	uint32_t mac_cfg1, xaui_cfg;
	uint32_t netwk_inf;
	int iface = port & 0x3;

	switch(port_type) {
	case SGMIIC:
		netwk_inf = nlm_read_nae_reg(nae_base,
		    SGMII_NET_IFACE_CTRL(nblock, iface));
		nlm_write_nae_reg(nae_base,
		    SGMII_NET_IFACE_CTRL(nblock, iface),
		    netwk_inf		|
		    (1 << 2));			/* enable tx */
		mac_cfg1 = nlm_read_nae_reg(nae_base,
		    SGMII_MAC_CONF1(nblock, iface));
		nlm_write_nae_reg(nae_base,
		    SGMII_MAC_CONF1(nblock, iface),
		    mac_cfg1		|
		    (1 << 2)		|	/* rx enable */
		    1);				/* tx enable */
		break;
	case XAUIC:
		xaui_cfg = nlm_read_nae_reg(nae_base,
		    XAUI_CONFIG1(nblock));
		nlm_write_nae_reg(nae_base,
		    XAUI_CONFIG1(nblock),
		    xaui_cfg		|
		    XAUI_CONFIG_TFEN	|
		    XAUI_CONFIG_RFEN);
		break;
	case ILC:
		break;
	}
}