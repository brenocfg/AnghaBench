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
typedef  int uint32_t ;
struct ip17x_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IP175C_MODE_PHY ; 
 int /*<<< orphan*/  IP175C_MODE_REG ; 
 int /*<<< orphan*/  IP175C_RESET_PHY ; 
 int /*<<< orphan*/  IP175C_RESET_REG ; 
 int ip17x_readphy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ip17x_writephy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ip175c_reset(struct ip17x_softc *sc)
{
	uint32_t data;

	/* Reset all the switch settings. */
	if (ip17x_writephy(sc->sc_dev, IP175C_RESET_PHY, IP175C_RESET_REG,
	    0x175c))
		return (-1);
	DELAY(2000);

	/* Force IP175C mode. */
	data = ip17x_readphy(sc->sc_dev, IP175C_MODE_PHY, IP175C_MODE_REG);
	if (data == 0x175a) {
		if (ip17x_writephy(sc->sc_dev, IP175C_MODE_PHY, IP175C_MODE_REG,
		    0x175c))
		return (-1);
	}

	return (0);
}