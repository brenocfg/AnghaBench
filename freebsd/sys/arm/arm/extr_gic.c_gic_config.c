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
typedef  int uint32_t ;
typedef  int u_int ;
struct arm_gic_softc {int /*<<< orphan*/  mutex; } ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  GICD_ICFGR (int) ; 
 int GICD_ICFGR_POL_HIGH ; 
 int GICD_ICFGR_POL_LOW ; 
 int GICD_ICFGR_POL_MASK ; 
 int GICD_ICFGR_TRIG_EDGE ; 
 int GICD_ICFGR_TRIG_LVL ; 
 int GICD_ICFGR_TRIG_MASK ; 
 int GIC_FIRST_SPI ; 
 int INTR_POLARITY_HIGH ; 
 int INTR_POLARITY_LOW ; 
 int INTR_TRIGGER_EDGE ; 
 int INTR_TRIGGER_LEVEL ; 
 int gic_d_read_4 (struct arm_gic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_d_write_4 (struct arm_gic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gic_config(struct arm_gic_softc *sc, u_int irq, enum intr_trigger trig,
    enum intr_polarity pol)
{
	uint32_t reg;
	uint32_t mask;

	if (irq < GIC_FIRST_SPI)
		return;

	mtx_lock_spin(&sc->mutex);

	reg = gic_d_read_4(sc, GICD_ICFGR(irq));
	mask = (reg >> 2*(irq % 16)) & 0x3;

	if (pol == INTR_POLARITY_LOW) {
		mask &= ~GICD_ICFGR_POL_MASK;
		mask |= GICD_ICFGR_POL_LOW;
	} else if (pol == INTR_POLARITY_HIGH) {
		mask &= ~GICD_ICFGR_POL_MASK;
		mask |= GICD_ICFGR_POL_HIGH;
	}

	if (trig == INTR_TRIGGER_LEVEL) {
		mask &= ~GICD_ICFGR_TRIG_MASK;
		mask |= GICD_ICFGR_TRIG_LVL;
	} else if (trig == INTR_TRIGGER_EDGE) {
		mask &= ~GICD_ICFGR_TRIG_MASK;
		mask |= GICD_ICFGR_TRIG_EDGE;
	}

	/* Set mask */
	reg = reg & ~(0x3 << 2*(irq % 16));
	reg = reg | (mask << 2*(irq % 16));
	gic_d_write_4(sc, GICD_ICFGR(irq), reg);

	mtx_unlock_spin(&sc->mutex);
}