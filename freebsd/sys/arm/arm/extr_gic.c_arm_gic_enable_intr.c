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
struct intr_irqsrc {int dummy; } ;
struct gic_irqsrc {int /*<<< orphan*/  gi_irq; } ;
struct arm_gic_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 struct arm_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_irq_unmask (struct arm_gic_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_gic_enable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct arm_gic_softc *sc = device_get_softc(dev);
	struct gic_irqsrc *gi = (struct gic_irqsrc *)isrc;

	arm_irq_memory_barrier(gi->gi_irq);
	gic_irq_unmask(sc, gi->gi_irq);
}