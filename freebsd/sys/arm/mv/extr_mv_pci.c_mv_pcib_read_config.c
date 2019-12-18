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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct mv_pcib_softc {int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_REG_STATUS ; 
 int PCIE_STATUS_LINK_DOWN ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mv_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int mv_pcib_hw_cfgread (struct mv_pcib_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mv_pcib_root_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
mv_pcib_read_config(device_t dev, u_int bus, u_int slot, u_int func,
    u_int reg, int bytes)
{
	struct mv_pcib_softc *sc = device_get_softc(dev);

	/* Return ~0 if link is inactive or trying to read from Root */
	if ((bus_space_read_4(sc->sc_bst, sc->sc_bsh, PCIE_REG_STATUS) &
	    PCIE_STATUS_LINK_DOWN) || mv_pcib_root_slot(dev, bus, slot, func))
		return (~0U);

	return (mv_pcib_hw_cfgread(sc, bus, slot, func, reg, bytes));
}