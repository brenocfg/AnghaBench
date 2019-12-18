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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct intr_irqsrc {int dummy; } ;
struct gic_irqsrc {int /*<<< orphan*/  gi_irq; } ;
struct arm_gicv2m_softc {int /*<<< orphan*/  sc_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ GICv2M_MSI_SETSPI_NS ; 
 struct arm_gicv2m_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_virtual (int /*<<< orphan*/ ) ; 
 scalar_t__ vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_gicv2m_map_msi(device_t dev, device_t child, struct intr_irqsrc *isrc,
    uint64_t *addr, uint32_t *data)
{
	struct arm_gicv2m_softc *sc = device_get_softc(dev);
	struct gic_irqsrc *gi = (struct gic_irqsrc *)isrc;

	*addr = vtophys(rman_get_virtual(sc->sc_mem)) + GICv2M_MSI_SETSPI_NS;
	*data = gi->gi_irq;

	return (0);
}