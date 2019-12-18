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
struct gic_irqsrc {scalar_t__ gi_irq; } ;
struct arm_gic_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SETOF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ GIC_FIRST_SPI ; 
 int /*<<< orphan*/  all_cpus ; 
 struct arm_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int gic_bind (struct arm_gic_softc*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gic_irq_cpu ; 
 int /*<<< orphan*/  intr_irq_next_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arm_gic_bind_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct arm_gic_softc *sc = device_get_softc(dev);
	struct gic_irqsrc *gi = (struct gic_irqsrc *)isrc;

	if (gi->gi_irq < GIC_FIRST_SPI)
		return (EINVAL);

	if (CPU_EMPTY(&isrc->isrc_cpu)) {
		gic_irq_cpu = intr_irq_next_cpu(gic_irq_cpu, &all_cpus);
		CPU_SETOF(gic_irq_cpu, &isrc->isrc_cpu);
	}
	return (gic_bind(sc, gi->gi_irq, &isrc->isrc_cpu));
}