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
struct rk_i2c_softc {int busy; scalar_t__ transfer_done; int /*<<< orphan*/  mtx; void* mode; } ;
struct iic_msg {int* buf; int len; int flags; int slave; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int IIC_M_NOSTART ; 
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int IIC_M_WR ; 
 int LSB ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  RK_I2C_CON ; 
 void* RK_I2C_CON_MODE_RRX ; 
 void* RK_I2C_CON_MODE_RX ; 
 void* RK_I2C_CON_MODE_TX ; 
 int /*<<< orphan*/  RK_I2C_IEN ; 
 int /*<<< orphan*/  RK_I2C_IPD ; 
 int RK_I2C_IPD_ALL ; 
 int /*<<< orphan*/  RK_I2C_LOCK (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  RK_I2C_MRXADDR ; 
 int RK_I2C_MRXADDR_VALID (int) ; 
 int /*<<< orphan*/  RK_I2C_MRXRADDR ; 
 int /*<<< orphan*/  RK_I2C_UNLOCK (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  RK_I2C_WRITE (struct rk_i2c_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cold ; 
 struct rk_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int msleep (struct rk_i2c_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_sleep (struct rk_i2c_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_i2c_intr_locked (struct rk_i2c_softc*) ; 
 int /*<<< orphan*/  rk_i2c_start_xfer (struct rk_i2c_softc*,struct iic_msg*,int) ; 

__attribute__((used)) static int
rk_i2c_transfer(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	struct rk_i2c_softc *sc;
	uint32_t reg;
	bool last_msg;
	int i, j, timeout, err;

	sc = device_get_softc(dev);

	RK_I2C_LOCK(sc);

	while (sc->busy)
		mtx_sleep(sc, &sc->mtx, 0, "i2cbuswait", 0);
	sc->busy = 1;

	/* Disable the module and interrupts */
	RK_I2C_WRITE(sc, RK_I2C_CON, 0);
	RK_I2C_WRITE(sc, RK_I2C_IEN, 0);

	/* Clean stale interrupts */
	RK_I2C_WRITE(sc, RK_I2C_IPD, RK_I2C_IPD_ALL);

	err = 0;
	for (i = 0; i < nmsgs; i++) {
		/* Validate parameters. */
		if (msgs == NULL || msgs[i].buf == NULL ||
		    msgs[i].len == 0) {
			err = EINVAL;
			break;
		}
		/*
		 * If next message have NOSTART flag, then they both
		 * should be same type (read/write) and same address.
		 */
		if (i < nmsgs - 1) {
			if ((msgs[i + 1].flags & IIC_M_NOSTART) &&
			    ((msgs[i].flags & IIC_M_RD) !=
			    (msgs[i + 1].flags & IIC_M_RD) ||
			    (msgs[i].slave !=  msgs[i + 1].slave))) {
				err = EINVAL;
				break;
			}
		}
		/*
		 * Detect simple register read case.
		 * The first message should be IIC_M_WR | IIC_M_NOSTOP,
		 * next pure IIC_M_RD (no other flags allowed). Both
		 * messages should have same slave address.
		 */

		if (nmsgs - i >= 2 && msgs[i].len < 4 &&
		    msgs[i].flags == (IIC_M_WR  | IIC_M_NOSTOP) &&
		    msgs[i + 1].flags == IIC_M_RD &&
		    (msgs[i].slave & ~LSB) == (msgs[i + 1].slave & ~LSB)) {
			sc->mode = RK_I2C_CON_MODE_RRX;

			/* Write slave address */
			reg = msgs[i].slave & ~LSB;
			reg |= RK_I2C_MRXADDR_VALID(0);
			RK_I2C_WRITE(sc, RK_I2C_MRXADDR, reg);

			/* Write slave register address */
			reg = 0;
			for (j = 0; j < msgs[i].len ; j++) {
				reg |= (msgs[i].buf[j] & 0xff) << (j * 8);
				reg |= RK_I2C_MRXADDR_VALID(j);
			}
			RK_I2C_WRITE(sc, RK_I2C_MRXRADDR, reg);

			i++;
		} else {
			if (msgs[i].flags & IIC_M_RD) {
				if (msgs[i].flags & IIC_M_NOSTART) {
					sc->mode = RK_I2C_CON_MODE_RX;
				} else {
					sc->mode = RK_I2C_CON_MODE_RRX;
					reg = msgs[i].slave & LSB;
					reg |= RK_I2C_MRXADDR_VALID(0);
					RK_I2C_WRITE(sc, RK_I2C_MRXADDR, reg);
					RK_I2C_WRITE(sc, RK_I2C_MRXRADDR, 0);
				}
			} else {
				sc->mode = RK_I2C_CON_MODE_TX;
			}
		}
		/* last message ? */
		last_msg = (i > nmsgs - 1) ||
		    !(msgs[i + 1].flags & IIC_M_NOSTART);
		rk_i2c_start_xfer(sc, msgs + i, last_msg);

		if (cold) {
			for(timeout = 10000; timeout > 0; timeout--)  {
				rk_i2c_intr_locked(sc);
				if (sc->transfer_done != 0)
					break;
				DELAY(100);
			}
			if (timeout <= 0)
				err = ETIMEDOUT;
		} else {
			while (err == 0 && sc->transfer_done != 1) {
				err = msleep(sc, &sc->mtx, PZERO, "rk_i2c",
				    10 * hz);
			}
		}
	}

	/* Disable the module and interrupts */
	RK_I2C_WRITE(sc, RK_I2C_CON, 0);
	RK_I2C_WRITE(sc, RK_I2C_IEN, 0);

	sc->busy = 0;

	RK_I2C_UNLOCK(sc);
	return (err);
}