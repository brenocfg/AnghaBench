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
struct gic_irqsrc {int gi_flags; int /*<<< orphan*/  gi_irq; } ;
struct arm_gic_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GICC_EOIR ; 
 int GI_FLAG_EARLY_EOI ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 struct arm_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_c_write_4 (struct arm_gic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_gic_post_filter(device_t dev, struct intr_irqsrc *isrc)
{
	struct arm_gic_softc *sc = device_get_softc(dev);
	struct gic_irqsrc *gi = (struct gic_irqsrc *)isrc;

        /* EOI for edge-triggered done earlier. */
	if ((gi->gi_flags & GI_FLAG_EARLY_EOI) == GI_FLAG_EARLY_EOI)
		return;

	arm_irq_memory_barrier(0);
	gic_c_write_4(sc, GICC_EOIR, gi->gi_irq);
}