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
typedef  int uint16_t ;
struct kiic_softc {int sc_flags; int* sc_data; int sc_resid; int sc_i2c_base; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_dev; } ;
struct iic_msg {int flags; int len; int* buf; int slave; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR ; 
 int /*<<< orphan*/  CONTROL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int I2C_BUSY ; 
 int /*<<< orphan*/  I2C_COMBMODE ; 
 int I2C_CT_ADDR ; 
 int I2C_ERROR ; 
 int I2C_READING ; 
 int /*<<< orphan*/  I2C_STDMODE ; 
 int /*<<< orphan*/  I2C_STDSUBMODE ; 
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int /*<<< orphan*/  ISR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  SUBADDR ; 
 struct kiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int kiic_readreg (struct kiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kiic_setmode (struct kiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kiic_setport (struct kiic_softc*,int) ; 
 int /*<<< orphan*/  kiic_writereg (struct kiic_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kiic_transfer(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	struct kiic_softc *sc;
	int i, x, timo, err;
	uint16_t addr;
	uint8_t subaddr;

	sc = device_get_softc(dev);
	timo = 100;
	subaddr = 0;

	mtx_lock(&sc->sc_mutex);

	if (sc->sc_flags & I2C_BUSY)
		mtx_sleep(dev, &sc->sc_mutex, 0, "kiic", timo);

	if (sc->sc_flags & I2C_BUSY) {
		mtx_unlock(&sc->sc_mutex);
		return (ETIMEDOUT);
	}
		
	sc->sc_flags = I2C_BUSY;

	/* Clear pending interrupts, and reset controller */
	kiic_writereg(sc, ISR, kiic_readreg(sc, ISR));
	kiic_writereg(sc, STATUS, 0);

	for (i = 0; i < nmsgs; i++) {
		if (msgs[i].flags & IIC_M_NOSTOP) {
			if (msgs[i+1].flags & IIC_M_RD)
				kiic_setmode(sc, I2C_COMBMODE);
			else
				kiic_setmode(sc, I2C_STDSUBMODE);
			KASSERT(msgs[i].len == 1, ("oversize I2C message"));
			subaddr = msgs[i].buf[0];
			i++;
		} else {
			kiic_setmode(sc, I2C_STDMODE);
		}

		sc->sc_data = msgs[i].buf;
		sc->sc_resid = msgs[i].len;
		sc->sc_flags = I2C_BUSY;
		addr = msgs[i].slave;
		timo = 1000 + sc->sc_resid * 200;
		timo += 100000;

		if (msgs[i].flags & IIC_M_RD) {
			sc->sc_flags |= I2C_READING;
			addr |= 1;
		}

		addr |= sc->sc_i2c_base;

		kiic_setport(sc, (addr & 0x100) >> 8);
		kiic_writereg(sc, ADDR, addr & 0xff);
		kiic_writereg(sc, SUBADDR, subaddr);

		x = kiic_readreg(sc, CONTROL) | I2C_CT_ADDR;
		kiic_writereg(sc, CONTROL, x);

		err = mtx_sleep(dev, &sc->sc_mutex, 0, "kiic", timo);
		
		msgs[i].len -= sc->sc_resid;

		if ((sc->sc_flags & I2C_ERROR) || err == EWOULDBLOCK) {
			device_printf(sc->sc_dev, "I2C error\n");
			sc->sc_flags = 0;
			mtx_unlock(&sc->sc_mutex);
			return (EIO);
		}
	}

	sc->sc_flags = 0;

	mtx_unlock(&sc->sc_mutex);

	return (0);
}