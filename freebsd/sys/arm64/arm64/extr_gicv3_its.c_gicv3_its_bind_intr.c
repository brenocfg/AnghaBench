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
struct intr_irqsrc {int /*<<< orphan*/  isrc_cpu; } ;
struct gicv3_its_softc {int /*<<< orphan*/  gic_irq_cpu; int /*<<< orphan*/  sc_cpus; } ;
struct gicv3_its_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SETOF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_irq_next_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  its_cmd_movi (int /*<<< orphan*/ ,struct gicv3_its_irqsrc*) ; 

__attribute__((used)) static int
gicv3_its_bind_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct gicv3_its_irqsrc *girq;
	struct gicv3_its_softc *sc;

	sc = device_get_softc(dev);
	girq = (struct gicv3_its_irqsrc *)isrc;
	if (CPU_EMPTY(&isrc->isrc_cpu)) {
		sc->gic_irq_cpu = intr_irq_next_cpu(sc->gic_irq_cpu,
		    &sc->sc_cpus);
		CPU_SETOF(sc->gic_irq_cpu, &isrc->isrc_cpu);
	}

	its_cmd_movi(dev, girq);

	return (0);
}