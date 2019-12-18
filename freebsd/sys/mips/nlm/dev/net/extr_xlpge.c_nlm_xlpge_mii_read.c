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
 int nlm_gmac_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
nlm_xlpge_mii_read(device_t dev, int phyaddr, int regidx)
{
	struct nlm_xlpge_softc *sc;
	int val;

	sc = device_get_softc(dev);
	if (sc->type == SGMIIC)
		val = nlm_gmac_mdio_read(sc->base_addr, sc->mdio_bus,
		    BLOCK_7, LANE_CFG, phyaddr, regidx);
	else
		val = 0xffff;

	return (val);
}