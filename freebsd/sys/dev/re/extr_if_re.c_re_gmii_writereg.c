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
typedef  int u_int32_t ;
struct rl_softc {int /*<<< orphan*/  rl_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_4 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RL_PHYAR ; 
 int RL_PHYAR_BUSY ; 
 int RL_PHYAR_PHYDATA ; 
 int RL_PHY_TIMEOUT ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
re_gmii_writereg(device_t dev, int phy, int reg, int data)
{
	struct rl_softc		*sc;
	u_int32_t		rval;
	int			i;

	sc = device_get_softc(dev);

	CSR_WRITE_4(sc, RL_PHYAR, (reg << 16) |
	    (data & RL_PHYAR_PHYDATA) | RL_PHYAR_BUSY);

	for (i = 0; i < RL_PHY_TIMEOUT; i++) {
		rval = CSR_READ_4(sc, RL_PHYAR);
		if (!(rval & RL_PHYAR_BUSY))
			break;
		DELAY(25);
	}

	if (i == RL_PHY_TIMEOUT) {
		device_printf(sc->rl_dev, "PHY write failed\n");
		return (0);
	}

	/*
	 * Controller requires a 20us delay to process next MDIO request.
	 */
	DELAY(20);

	return (0);
}