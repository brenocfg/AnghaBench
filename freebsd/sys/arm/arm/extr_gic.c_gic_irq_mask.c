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
typedef  int /*<<< orphan*/  u_int ;
struct arm_gic_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GICD_ICENABLER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GICD_I_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_d_write_4 (struct arm_gic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
gic_irq_mask(struct arm_gic_softc *sc, u_int irq)
{

	gic_d_write_4(sc, GICD_ICENABLER(irq), GICD_I_MASK(irq));
}