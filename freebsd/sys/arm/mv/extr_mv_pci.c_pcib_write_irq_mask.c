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
struct mv_pcib_softc {scalar_t__ sc_type; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;

/* Variables and functions */
 scalar_t__ MV_TYPE_PCIE ; 
 int /*<<< orphan*/  PCIE_REG_IRQ_MASK ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pcib_write_irq_mask(struct mv_pcib_softc *sc, uint32_t mask)
{

	if (sc->sc_type != MV_TYPE_PCIE)
		return;

	bus_space_write_4(sc->sc_bst, sc->sc_bsh, PCIE_REG_IRQ_MASK, mask);
}