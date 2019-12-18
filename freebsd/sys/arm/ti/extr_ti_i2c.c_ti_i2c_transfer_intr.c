#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct ti_i2c_softc {scalar_t__ sc_error; int sc_con_reg; int sc_buffer_pos; TYPE_1__* sc_buffer; int /*<<< orphan*/  sc_fifo_trsh; } ;
struct TYPE_2__ {int flags; int len; int* buf; } ;

/* Variables and functions */
 void* ENXIO ; 
 int I2C_CON_STP ; 
 int /*<<< orphan*/  I2C_REG_CON ; 
 int /*<<< orphan*/  I2C_REG_DATA ; 
 int /*<<< orphan*/  I2C_REG_STATUS ; 
 int I2C_STAT_AL ; 
 int I2C_STAT_ARDY ; 
 int I2C_STAT_NACK ; 
 int I2C_STAT_RDR ; 
 int I2C_STAT_RRDY ; 
 int I2C_STAT_XDR ; 
 int I2C_STAT_XRDY ; 
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ti_i2c_dbg (struct ti_i2c_softc*,char*) ; 
 int ti_i2c_read_2 (struct ti_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_i2c_write_2 (struct ti_i2c_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ti_i2c_transfer_intr(struct ti_i2c_softc* sc, uint16_t status)
{
	int amount, done, i;

	done = 0;
	amount = 0;
	/* Check for the error conditions. */
	if (status & I2C_STAT_NACK) {
		/* No ACK from slave. */
		ti_i2c_dbg(sc, "NACK\n");
		ti_i2c_write_2(sc, I2C_REG_STATUS, I2C_STAT_NACK);
		sc->sc_error = ENXIO;
	} else if (status & I2C_STAT_AL) {
		/* Arbitration lost. */
		ti_i2c_dbg(sc, "Arbitration lost\n");
		ti_i2c_write_2(sc, I2C_REG_STATUS, I2C_STAT_AL);
		sc->sc_error = ENXIO;
	}

	/* Check if we have finished. */
	if (status & I2C_STAT_ARDY) {
		/* Register access ready - transaction complete basically. */
		ti_i2c_dbg(sc, "ARDY transaction complete\n");
		if (sc->sc_error != 0 && sc->sc_buffer->flags & IIC_M_NOSTOP) {
			ti_i2c_write_2(sc, I2C_REG_CON,
			    sc->sc_con_reg | I2C_CON_STP);
		}
		ti_i2c_write_2(sc, I2C_REG_STATUS,
		    I2C_STAT_ARDY | I2C_STAT_RDR | I2C_STAT_RRDY |
		    I2C_STAT_XDR | I2C_STAT_XRDY);
		return (1);
	}

	if (sc->sc_buffer->flags & IIC_M_RD) {
		/* Read some data. */
		if (status & I2C_STAT_RDR) {
			/*
			 * Receive draining interrupt - last data received.
			 * The set FIFO threshold won't be reached to trigger
			 * RRDY.
			 */
			ti_i2c_dbg(sc, "Receive draining interrupt\n");

			/*
			 * Drain the FIFO.  Read the pending data in the FIFO.
			 */
			amount = sc->sc_buffer->len - sc->sc_buffer_pos;
		} else if (status & I2C_STAT_RRDY) {
			/*
			 * Receive data ready interrupt - FIFO has reached the
			 * set threshold.
			 */
			ti_i2c_dbg(sc, "Receive data ready interrupt\n");

			amount = min(sc->sc_fifo_trsh,
			    sc->sc_buffer->len - sc->sc_buffer_pos);
		}

		/* Read the bytes from the fifo. */
		for (i = 0; i < amount; i++)
			sc->sc_buffer->buf[sc->sc_buffer_pos++] = 
			    (uint8_t)(ti_i2c_read_2(sc, I2C_REG_DATA) & 0xff);

		if (status & I2C_STAT_RDR)
			ti_i2c_write_2(sc, I2C_REG_STATUS, I2C_STAT_RDR);
		if (status & I2C_STAT_RRDY)
			ti_i2c_write_2(sc, I2C_REG_STATUS, I2C_STAT_RRDY);

	} else {
		/* Write some data. */
		if (status & I2C_STAT_XDR) {
			/*
			 * Transmit draining interrupt - FIFO level is below
			 * the set threshold and the amount of data still to
			 * be transferred won't reach the set FIFO threshold.
			 */
			ti_i2c_dbg(sc, "Transmit draining interrupt\n");

			/*
			 * Drain the TX data.  Write the pending data in the
			 * FIFO.
			 */
			amount = sc->sc_buffer->len - sc->sc_buffer_pos;
		} else if (status & I2C_STAT_XRDY) {
			/*
			 * Transmit data ready interrupt - the FIFO level
			 * is below the set threshold.
			 */
			ti_i2c_dbg(sc, "Transmit data ready interrupt\n");

			amount = min(sc->sc_fifo_trsh,
			    sc->sc_buffer->len - sc->sc_buffer_pos);
		}

		/* Write the bytes from the fifo. */
		for (i = 0; i < amount; i++)
			ti_i2c_write_2(sc, I2C_REG_DATA,
			    sc->sc_buffer->buf[sc->sc_buffer_pos++]);

		if (status & I2C_STAT_XDR)
			ti_i2c_write_2(sc, I2C_REG_STATUS, I2C_STAT_XDR);
		if (status & I2C_STAT_XRDY)
			ti_i2c_write_2(sc, I2C_REG_STATUS, I2C_STAT_XRDY);
	}

	return (done);
}