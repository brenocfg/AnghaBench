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
typedef  int /*<<< orphan*/  ig4iic_softc_t ;

/* Variables and functions */
 int IG4_I2C_ABORT ; 
 int IG4_I2C_ENABLE ; 
 int /*<<< orphan*/  IG4_INTR_STOP_DET ; 
 int IIC_ESTATUS ; 
 int /*<<< orphan*/  set_controller (int /*<<< orphan*/ *,int) ; 
 int wait_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ig4iic_xfer_abort(ig4iic_softc_t *sc)
{
	int error;

	/* Request send of STOP condition and flush of TX FIFO */
	set_controller(sc, IG4_I2C_ABORT | IG4_I2C_ENABLE);
	/*
	 * Wait for the TX_ABRT interrupt with ABRTSRC_TRANSFER
	 * bit set in TX_ABRT_SOURCE register.
	 */
	error = wait_intr(sc, IG4_INTR_STOP_DET);
	set_controller(sc, IG4_I2C_ENABLE);

	return (error == IIC_ESTATUS ? 0 : error);
}