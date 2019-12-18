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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ig4iic_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IG4_REG_CLR_INTR ; 
 int /*<<< orphan*/  reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_slave_addr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ig4iic_xfer_start(ig4iic_softc_t *sc, uint16_t slave, bool repeated_start)
{
	set_slave_addr(sc, slave >> 1);

	if (!repeated_start) {
		/*
		 * Clear any previous TX/RX FIFOs overflow/underflow bits
		 * and I2C bus STOP condition.
		 */
		reg_read(sc, IG4_REG_CLR_INTR);
	}

	return (0);
}