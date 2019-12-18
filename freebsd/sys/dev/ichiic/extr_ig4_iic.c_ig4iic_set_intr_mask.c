#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ intr_mask; } ;
typedef  TYPE_1__ ig4iic_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IG4_REG_INTR_MASK ; 
 int /*<<< orphan*/  reg_write (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ig4iic_set_intr_mask(ig4iic_softc_t *sc, uint32_t val)
{
	if (sc->intr_mask != val) {
		reg_write(sc, IG4_REG_INTR_MASK, val);
		sc->intr_mask = val;
	}
}