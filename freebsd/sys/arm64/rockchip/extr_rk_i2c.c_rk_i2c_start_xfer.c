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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct rk_i2c_softc {int transfer_done; int nak_recv; int tx_slave_addr; int msg_len; int mode; int /*<<< orphan*/  state; struct iic_msg* msg; scalar_t__ cnt; } ;
struct iic_msg {int len; int flags; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int IIC_M_NOSTART ; 
 int /*<<< orphan*/  RK_I2C_CON ; 
 int RK_I2C_CON_CTRL_MASK ; 
 int RK_I2C_CON_EN ; 
 int RK_I2C_CON_LASTACK ; 
 int RK_I2C_CON_MODE_RX ; 
 int RK_I2C_CON_MODE_SHIFT ; 
 int RK_I2C_CON_MODE_TX ; 
 int RK_I2C_CON_START ; 
 int /*<<< orphan*/  RK_I2C_IEN ; 
 int RK_I2C_IEN_MBRFIEN ; 
 int RK_I2C_IEN_MBTFIEN ; 
 int RK_I2C_IEN_NAKRCVIEN ; 
 int RK_I2C_IEN_STARTIEN ; 
 int /*<<< orphan*/  RK_I2C_MRXCNT ; 
 int /*<<< orphan*/  RK_I2C_MTXCNT ; 
 int RK_I2C_READ (struct rk_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_I2C_WRITE (struct rk_i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  STATE_READ ; 
 int /*<<< orphan*/  STATE_START ; 
 int /*<<< orphan*/  STATE_WRITE ; 
 int rk_i2c_fill_tx (struct rk_i2c_softc*) ; 

__attribute__((used)) static void
rk_i2c_start_xfer(struct rk_i2c_softc *sc, struct iic_msg *msg, boolean_t last)
{
	uint32_t reg;
	uint8_t len;

	sc->transfer_done = false;
	sc->nak_recv = false;
	sc->tx_slave_addr = false;
	sc->cnt = 0;
	sc->state = STATE_IDLE;
	sc->msg = msg;
	sc->msg_len = sc->msg->len;

	reg = RK_I2C_READ(sc, RK_I2C_CON) & ~RK_I2C_CON_CTRL_MASK;
	if (!(sc->msg->flags & IIC_M_NOSTART)) {
		/* Stadard message */
		if (sc->mode == RK_I2C_CON_MODE_TX) {
			sc->msg_len++;	/* Take slave address in account. */
			sc->tx_slave_addr = true;
		}
		sc->state = STATE_START;
		reg |= RK_I2C_CON_START;

		RK_I2C_WRITE(sc, RK_I2C_IEN, RK_I2C_IEN_STARTIEN);
	} else {
		/* Continuation message */
		if (sc->mode == RK_I2C_CON_MODE_RX) {
			sc->state = STATE_READ;
			if (last)
				reg |= RK_I2C_CON_LASTACK;

			RK_I2C_WRITE(sc, RK_I2C_MRXCNT, sc->msg->len);
			RK_I2C_WRITE(sc, RK_I2C_IEN, RK_I2C_IEN_MBRFIEN |
			    RK_I2C_IEN_NAKRCVIEN);
		} else {
			sc->state = STATE_WRITE;
			len = rk_i2c_fill_tx(sc);

			RK_I2C_WRITE(sc, RK_I2C_MTXCNT, len);

			RK_I2C_WRITE(sc, RK_I2C_IEN, RK_I2C_IEN_MBTFIEN |
			    RK_I2C_IEN_NAKRCVIEN);
		}
	}
	reg |= sc->mode << RK_I2C_CON_MODE_SHIFT;
	reg |= RK_I2C_CON_EN;
	RK_I2C_WRITE(sc, RK_I2C_CON, reg);
}