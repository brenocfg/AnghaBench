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
 int /*<<< orphan*/  GICC_EOIR ; 
 int /*<<< orphan*/  arm_gic_disable_intr (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 struct arm_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_c_write_4 (struct arm_gic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_gic_pre_ithread(device_t dev, struct intr_irqsrc *isrc)
{
	struct arm_gic_softc *sc = device_get_softc(dev);
	struct gic_irqsrc *gi = (struct gic_irqsrc *)isrc;

	arm_gic_disable_intr(dev, isrc);
	gic_c_write_4(sc, GICC_EOIR, gi->gi_irq);
}