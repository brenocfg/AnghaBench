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
struct mgb_softc {int /*<<< orphan*/ * regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MGB_BAR ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_alloc_regs(struct mgb_softc *sc)
{
	int rid;

	rid = PCIR_BAR(MGB_BAR);
	pci_enable_busmaster(sc->dev);
	sc->regs = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (sc->regs == NULL)
		 return ENXIO;

	return (0);
}