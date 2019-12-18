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
struct ether_addr {int dummy; } ;
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR0 ; 
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR0_BYTE4 ; 
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR0_BYTE5 ; 
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR1 ; 
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR1_BYTE0 ; 
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR1_BYTE1 ; 
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR1_BYTE2 ; 
 int /*<<< orphan*/  AR8X16_REG_SW_MAC_ADDR1_BYTE3 ; 
 char MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arswitch_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8xxx_hw_get_switch_macaddr(struct arswitch_softc *sc, struct ether_addr *ea)
{
	uint32_t ret0, ret1;
	char *s;

	s = (void *) ea;

	ret0 = arswitch_readreg(sc->sc_dev, AR8X16_REG_SW_MAC_ADDR0);
	ret1 = arswitch_readreg(sc->sc_dev, AR8X16_REG_SW_MAC_ADDR1);

	s[5] = MS(ret0, AR8X16_REG_SW_MAC_ADDR0_BYTE5);
	s[4] = MS(ret0, AR8X16_REG_SW_MAC_ADDR0_BYTE4);
	s[3] = MS(ret1, AR8X16_REG_SW_MAC_ADDR1_BYTE3);
	s[2] = MS(ret1, AR8X16_REG_SW_MAC_ADDR1_BYTE2);
	s[1] = MS(ret1, AR8X16_REG_SW_MAC_ADDR1_BYTE1);
	s[0] = MS(ret1, AR8X16_REG_SW_MAC_ADDR1_BYTE0);

	return (0);
}