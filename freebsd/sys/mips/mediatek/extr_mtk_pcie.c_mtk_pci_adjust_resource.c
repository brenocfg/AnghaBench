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
struct rman {int dummy; } ;
struct resource {int dummy; } ;
struct mtk_pci_softc {struct rman sc_mem_rman; struct rman sc_io_rman; struct rman sc_irq_rman; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  PCI_RES_BUS 131 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int bus_generic_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_domain_adjust_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_adjust_resource (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pci_adjust_resource(device_t bus, device_t child, int type,
    struct resource *res, rman_res_t start, rman_res_t end)
{
	struct mtk_pci_softc *sc = device_get_softc(bus);
	struct rman *rm;

	switch (type) {
	case PCI_RES_BUS:
		return pci_domain_adjust_bus(0, child, res, start, end);
	case SYS_RES_IRQ:
		rm = &sc->sc_irq_rman;
		break;
	case SYS_RES_IOPORT:
		rm = &sc->sc_io_rman;
		break;
	case SYS_RES_MEMORY:
		rm = &sc->sc_mem_rman;
		break;
	default:
		rm = NULL;
		break;
	}

	if (rm != NULL)
		return (rman_adjust_resource(res, start, end));

	return (bus_generic_adjust_resource(bus, child, type, res, start, end));
}