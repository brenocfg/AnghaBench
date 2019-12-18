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

/* Variables and functions */
 int /*<<< orphan*/  XAUIC ; 
 int /*<<< orphan*/  XAUI_MAC_ADDR0_HI (int) ; 
 int /*<<< orphan*/  XAUI_MAC_ADDR0_LO (int) ; 
 int /*<<< orphan*/  XAUI_MAC_ADDR_MASK0_HI (int) ; 
 int /*<<< orphan*/  XAUI_MAC_ADDR_MASK0_LO (int) ; 
 int /*<<< orphan*/  nlm_nae_setup_rx_mode_xaui (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_nae_setup_mac_addr_xaui(uint64_t base, int nblock, int iface,
    int port_type, unsigned char *mac_addr)
{
	nlm_write_nae_reg(base,
	    XAUI_MAC_ADDR0_LO(nblock),
	    (mac_addr[5] << 24) |
	    (mac_addr[4] << 16) |
	    (mac_addr[3] << 8)  |
	    mac_addr[2]);

	nlm_write_nae_reg(base,
	    XAUI_MAC_ADDR0_HI(nblock),
	    (mac_addr[1] << 24) |
	    (mac_addr[0] << 16));

	nlm_write_nae_reg(base,
	    XAUI_MAC_ADDR_MASK0_LO(nblock),
	    0xffffffff);
	nlm_write_nae_reg(base,
	    XAUI_MAC_ADDR_MASK0_HI(nblock),
	    0xffffffff);

	nlm_nae_setup_rx_mode_xaui(base, nblock, iface,
	    XAUIC,
	    1, /* broadcast enabled */
	    1, /* multicast enabled */
	    0, /* do not accept pause frames */
	    0 /* promisc mode disabled */
	    );
}