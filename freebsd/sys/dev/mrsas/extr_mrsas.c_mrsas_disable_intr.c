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
typedef  int u_int32_t ;
struct mrsas_softc {int mask_interrupts; } ;

/* Variables and functions */
 int mrsas_read_reg (struct mrsas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrsas_reg_set ; 
 int /*<<< orphan*/  mrsas_write_reg (struct mrsas_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outbound_intr_mask ; 

void
mrsas_disable_intr(struct mrsas_softc *sc)
{
	u_int32_t mask = 0xFFFFFFFF;
	u_int32_t status;

	sc->mask_interrupts = 1;
	mrsas_write_reg(sc, offsetof(mrsas_reg_set, outbound_intr_mask), mask);
	/* Dummy read to force pci flush */
	status = mrsas_read_reg(sc, offsetof(mrsas_reg_set, outbound_intr_mask));
}