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
typedef  int /*<<< orphan*/  u_int32_t ;
struct mrsas_softc {scalar_t__ mask_interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_FUSION_ENABLE_INTERRUPT_MASK ; 
 int /*<<< orphan*/  mrsas_read_reg (struct mrsas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrsas_reg_set ; 
 int /*<<< orphan*/  mrsas_write_reg (struct mrsas_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outbound_intr_mask ; 
 int /*<<< orphan*/  outbound_intr_status ; 

void
mrsas_enable_intr(struct mrsas_softc *sc)
{
	u_int32_t mask = MFI_FUSION_ENABLE_INTERRUPT_MASK;
	u_int32_t status;

	sc->mask_interrupts = 0;
	mrsas_write_reg(sc, offsetof(mrsas_reg_set, outbound_intr_status), ~0);
	status = mrsas_read_reg(sc, offsetof(mrsas_reg_set, outbound_intr_status));

	mrsas_write_reg(sc, offsetof(mrsas_reg_set, outbound_intr_mask), ~mask);
	status = mrsas_read_reg(sc, offsetof(mrsas_reg_set, outbound_intr_mask));
}