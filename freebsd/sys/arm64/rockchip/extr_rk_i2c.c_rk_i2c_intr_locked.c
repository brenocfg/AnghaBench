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
typedef  int uint32_t ;
struct rk_i2c_softc {int ipd; int nak_recv; int transfer_done; int state; int cnt; TYPE_1__* msg; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int len; int flags; } ;

/* Variables and functions */
 int IIC_M_NOSTOP ; 
 int /*<<< orphan*/  RK_I2C_CON ; 
 int RK_I2C_CON_LASTACK ; 
 int /*<<< orphan*/  RK_I2C_CON_MODE_RRX ; 
 int /*<<< orphan*/  RK_I2C_CON_MODE_RX ; 
 int RK_I2C_CON_START ; 
 int RK_I2C_CON_STOP ; 
 int /*<<< orphan*/  RK_I2C_IEN ; 
 int RK_I2C_IEN_MBRFIEN ; 
 int RK_I2C_IEN_MBTFIEN ; 
 int RK_I2C_IEN_NAKRCVIEN ; 
 int /*<<< orphan*/  RK_I2C_IPD ; 
 int RK_I2C_IPD_ALL ; 
 int RK_I2C_IPD_NAKRCVIPD ; 
 int /*<<< orphan*/  RK_I2C_MRXCNT ; 
 int /*<<< orphan*/  RK_I2C_MTXCNT ; 
 void* RK_I2C_READ (struct rk_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK_I2C_WRITE (struct rk_i2c_softc*,int /*<<< orphan*/ ,int) ; 
#define  STATE_IDLE 132 
#define  STATE_READ 131 
#define  STATE_START 130 
#define  STATE_STOP 129 
#define  STATE_WRITE 128 
 int /*<<< orphan*/  rk_i2c_drain_rx (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  rk_i2c_fill_tx (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  rk_i2c_send_stop (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  wakeup (struct rk_i2c_softc*) ; 

__attribute__((used)) static void
rk_i2c_intr_locked(struct rk_i2c_softc *sc)
{
	uint32_t reg;

	sc->ipd = RK_I2C_READ(sc, RK_I2C_IPD);

	/* Something to handle? */
	if ((sc->ipd & RK_I2C_IPD_ALL) == 0)
		return;

	RK_I2C_WRITE(sc, RK_I2C_IPD, sc->ipd);
	sc->ipd &= RK_I2C_IPD_ALL;

	if (sc->ipd & RK_I2C_IPD_NAKRCVIPD) {
		/* NACK received */
		sc->ipd &= ~RK_I2C_IPD_NAKRCVIPD;
		sc->nak_recv = 1;
		/* XXXX last byte !!!, signal error !!! */
		sc->transfer_done = 1;
		sc->state = STATE_IDLE;
		goto err;
	}

	switch (sc->state) {
	case STATE_START:
		/* Disable start bit */
		reg = RK_I2C_READ(sc, RK_I2C_CON);
		reg &= ~RK_I2C_CON_START;
		RK_I2C_WRITE(sc, RK_I2C_CON, reg);

		if (sc->mode == RK_I2C_CON_MODE_RRX ||
		    sc->mode == RK_I2C_CON_MODE_RX) {
			sc->state = STATE_READ;
			RK_I2C_WRITE(sc, RK_I2C_IEN, RK_I2C_IEN_MBRFIEN |
			    RK_I2C_IEN_NAKRCVIEN);

			reg = RK_I2C_READ(sc, RK_I2C_CON);
			reg |= RK_I2C_CON_LASTACK;
			RK_I2C_WRITE(sc, RK_I2C_CON, reg);

			RK_I2C_WRITE(sc, RK_I2C_MRXCNT, sc->msg->len);
		} else {
			sc->state = STATE_WRITE;
			RK_I2C_WRITE(sc, RK_I2C_IEN, RK_I2C_IEN_MBTFIEN |
			    RK_I2C_IEN_NAKRCVIEN);

			sc->msg->len += 1;
			rk_i2c_fill_tx(sc);
			RK_I2C_WRITE(sc, RK_I2C_MTXCNT, sc->msg->len);
		}
		break;
	case STATE_READ:
		rk_i2c_drain_rx(sc);

		if (sc->cnt == sc->msg->len)
			rk_i2c_send_stop(sc);

		break;
	case STATE_WRITE:
		if (sc->cnt == sc->msg->len &&
		     !(sc->msg->flags & IIC_M_NOSTOP)) {
			rk_i2c_send_stop(sc);
			break;
		}
		/* passthru */
	case STATE_STOP:
		/* Disable stop bit */
		reg = RK_I2C_READ(sc, RK_I2C_CON);
		reg &= ~RK_I2C_CON_STOP;
		RK_I2C_WRITE(sc, RK_I2C_CON, reg);

		sc->transfer_done = 1;
		sc->state = STATE_IDLE;
		break;
	case STATE_IDLE:
		break;
	}

err:
	wakeup(sc);
}