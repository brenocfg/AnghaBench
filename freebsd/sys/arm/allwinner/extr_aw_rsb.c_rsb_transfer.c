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
struct rsb_softc {scalar_t__ type; int busy; int cur_addr; int /*<<< orphan*/ * msg; scalar_t__ status; int /*<<< orphan*/  mtx; } ;
struct iic_msg {int flags; int slave; int len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ A23_RSB ; 
 int CMD_RD16 ; 
 int CMD_RD32 ; 
 int CMD_RD8 ; 
 int CMD_WR16 ; 
 int CMD_WR32 ; 
 int CMD_WR8 ; 
 int DLEN_READ ; 
 int EINVAL ; 
 int IIC_M_RD ; 
 int /*<<< orphan*/  RSB_CMD ; 
 int /*<<< orphan*/  RSB_DADDR0 ; 
 int /*<<< orphan*/  RSB_DATA0 ; 
 int /*<<< orphan*/  RSB_DLEN ; 
 int /*<<< orphan*/  RSB_INTS ; 
 int /*<<< orphan*/  RSB_LOCK (struct rsb_softc*) ; 
 int RSB_MAXLEN ; 
 int RSB_READ (struct rsb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSB_UNLOCK (struct rsb_softc*) ; 
 int /*<<< orphan*/  RSB_WRITE (struct rsb_softc*,int /*<<< orphan*/ ,int) ; 
 struct rsb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_sleep (struct rsb_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsb_decode (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rsb_encode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rsb_set_rta (int /*<<< orphan*/ ,int) ; 
 int rsb_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct rsb_softc*) ; 

__attribute__((used)) static int
rsb_transfer(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	struct rsb_softc *sc;
	uint32_t daddr[2], data[2], dlen;
	uint16_t device_addr;
	uint8_t cmd;
	int error;

	sc = device_get_softc(dev);

	/*
	 * P2WI and RSB are not really I2C or SMBus controllers, so there are
	 * some restrictions imposed by the driver.
	 *
	 * Transfers must contain exactly two messages. The first is always
	 * a write, containing a single data byte offset. Data will either
	 * be read from or written to the corresponding data byte in the
	 * second message. The slave address in both messages must be the
	 * same.
	 */
	if (nmsgs != 2 || (msgs[0].flags & IIC_M_RD) == IIC_M_RD ||
	    (msgs[0].slave >> 1) != (msgs[1].slave >> 1) ||
	    msgs[0].len != 1 || msgs[1].len > RSB_MAXLEN)
		return (EINVAL);

	/* The RSB controller can read or write 1, 2, or 4 bytes at a time. */
	if (sc->type == A23_RSB) {
		if ((msgs[1].flags & IIC_M_RD) != 0) {
			switch (msgs[1].len) {
			case 1:
				cmd = CMD_RD8;
				break;
			case 2:
				cmd = CMD_RD16;
				break;
			case 4:
				cmd = CMD_RD32;
				break;
			default:
				return (EINVAL);
			}
		} else {
			switch (msgs[1].len) {
			case 1:
				cmd = CMD_WR8;
				break;
			case 2:
				cmd = CMD_WR16;
				break;
			case 4:
				cmd = CMD_WR32;
				break;
			default:
				return (EINVAL);
			}
		}
	}

	RSB_LOCK(sc);
	while (sc->busy)
		mtx_sleep(sc, &sc->mtx, 0, "i2cbuswait", 0);
	sc->busy = 1;
	sc->status = 0;

	/* Select current run-time address if necessary */
	if (sc->type == A23_RSB) {
		device_addr = msgs[0].slave >> 1;
		if (sc->cur_addr != device_addr) {
			error = rsb_set_rta(dev, device_addr);
			if (error != 0)
				goto done;
			sc->cur_addr = device_addr;
			sc->status = 0;
		}
	}

	/* Clear interrupt status */
	RSB_WRITE(sc, RSB_INTS, RSB_READ(sc, RSB_INTS));

	/* Program data access address registers */
	daddr[0] = rsb_encode(msgs[0].buf, msgs[0].len, 0);
	RSB_WRITE(sc, RSB_DADDR0, daddr[0]);

	/* Write data */
	if ((msgs[1].flags & IIC_M_RD) == 0) {
		data[0] = rsb_encode(msgs[1].buf, msgs[1].len, 0);
		RSB_WRITE(sc, RSB_DATA0, data[0]);
	}

	/* Set command type for RSB */
	if (sc->type == A23_RSB)
		RSB_WRITE(sc, RSB_CMD, cmd);

	/* Program data length register and transfer direction */
	dlen = msgs[0].len - 1;
	if ((msgs[1].flags & IIC_M_RD) == IIC_M_RD)
		dlen |= DLEN_READ;
	RSB_WRITE(sc, RSB_DLEN, dlen);

	/* Start transfer */
	error = rsb_start(dev);
	if (error != 0)
		goto done;

	/* Read data */
	if ((msgs[1].flags & IIC_M_RD) == IIC_M_RD) {
		data[0] = RSB_READ(sc, RSB_DATA0);
		rsb_decode(data[0], msgs[1].buf, msgs[1].len, 0);
	}

done:
	sc->msg = NULL;
	sc->busy = 0;
	wakeup(sc);
	RSB_UNLOCK(sc);

	return (error);
}