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
struct nlm_xlpge_softc {scalar_t__ type; int /*<<< orphan*/  mdio_bus; int /*<<< orphan*/  base_addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_7 ; 
 int /*<<< orphan*/  LANE_CFG ; 
 scalar_t__ SGMIIC ; 
 struct nlm_xlpge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_gmac_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
nlm_xlpge_mii_write(device_t dev, int phyaddr, int regidx, int val)
{
	struct nlm_xlpge_softc *sc;

	sc = device_get_softc(dev);
	if (sc->type == SGMIIC)
		nlm_gmac_mdio_write(sc->base_addr, sc->mdio_bus, BLOCK_7,
		    LANE_CFG, phyaddr, regidx, val);

	return (0);
}