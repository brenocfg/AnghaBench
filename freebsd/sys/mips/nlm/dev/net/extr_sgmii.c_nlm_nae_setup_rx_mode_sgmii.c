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
 int /*<<< orphan*/  SGMII_MAC_FILTER_CONFIG (int,int) ; 
 int /*<<< orphan*/  SGMII_NETIOR_VLANTYPE_FILTER (int,int) ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_nae_setup_rx_mode_sgmii(uint64_t base, int nblock, int iface, int port_type,
    int broadcast_en, int multicast_en, int pause_en, int promisc_en)
{
	uint32_t val;

	/* bit[17] of vlan_typefilter - allows packet matching in MAC.
	 * When DA filtering is disabled, this bit and bit[16] should
	 * be zero.
	 * bit[16] of vlan_typefilter - Allows hash matching to be used
	 * for DA filtering. When DA filtering is disabled, this bit and
	 * bit[17] should be zero.
	 * Both bits have to be set only if you want to turn on both
	 * features / modes.
	 */
	if (promisc_en == 1) {
		val = nlm_read_nae_reg(base,
		    SGMII_NETIOR_VLANTYPE_FILTER(nblock, iface));
		val &= (~(0x3 << 16));
		nlm_write_nae_reg(base,
		    SGMII_NETIOR_VLANTYPE_FILTER(nblock, iface), val);
	} else {
		val = nlm_read_nae_reg(base,
		    SGMII_NETIOR_VLANTYPE_FILTER(nblock, iface));
		val |= (0x1 << 17);
		nlm_write_nae_reg(base,
		    SGMII_NETIOR_VLANTYPE_FILTER(nblock, iface), val);
	}

	val = ((broadcast_en & 0x1) << 10)  |
	    ((pause_en & 0x1) << 9)     |
	    ((multicast_en & 0x1) << 8) |
	    ((promisc_en & 0x1) << 7)   | /* unicast_enable - enables promisc mode */
	    1; /* MAC address is always valid */

	nlm_write_nae_reg(base, SGMII_MAC_FILTER_CONFIG(nblock, iface), val);

}