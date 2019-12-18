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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bwn_phy_g {scalar_t__ pg_ofdmtab_dir; int pg_ofdmtab_addr; } ;
struct TYPE_2__ {struct bwn_phy_g phy_g; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_OFDMTAB_DIR_WRITE ; 
 int /*<<< orphan*/  BWN_PHY_OTABLECTL ; 
 int /*<<< orphan*/  BWN_PHY_OTABLEI ; 
 int /*<<< orphan*/  BWN_PHY_OTABLEQ ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_ofdmtab_write_4(struct bwn_mac *mac, uint16_t table, uint16_t offset,
    uint32_t value)
{
	struct bwn_phy_g *pg = &mac->mac_phy.phy_g;
	uint16_t addr;

	addr = table + offset;
	if ((pg->pg_ofdmtab_dir != BWN_OFDMTAB_DIR_WRITE) ||
	    (addr - 1 != pg->pg_ofdmtab_addr)) {
		BWN_PHY_WRITE(mac, BWN_PHY_OTABLECTL, addr);
		pg->pg_ofdmtab_dir = BWN_OFDMTAB_DIR_WRITE;
	}
	pg->pg_ofdmtab_addr = addr;

	BWN_PHY_WRITE(mac, BWN_PHY_OTABLEI, value);
	BWN_PHY_WRITE(mac, BWN_PHY_OTABLEQ, (value >> 16));
}