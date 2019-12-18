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
typedef  size_t uint8_t ;
typedef  int uint16_t ;
struct twl_softc {size_t* sc_subaddr_map; int /*<<< orphan*/  sc_dev; } ;
struct iic_msg {size_t slave; size_t* buf; scalar_t__ len; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 size_t TWL_INVALID_CHIP_ID ; 
 int /*<<< orphan*/  TWL_LOCK (struct twl_softc*) ; 
 int TWL_MAX_IIC_DATA_SIZE ; 
 int /*<<< orphan*/  TWL_UNLOCK (struct twl_softc*) ; 
 struct twl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

int
twl_write(device_t dev, uint8_t nsub, uint8_t reg, uint8_t *buf, uint16_t cnt)
{
	struct twl_softc *sc;
	struct iic_msg msg;
	uint8_t addr;
	uint8_t tmp_buf[TWL_MAX_IIC_DATA_SIZE + 1];
	int rc;

	if (cnt > TWL_MAX_IIC_DATA_SIZE)
		return (ENOMEM);

	/* Set the register address as the first byte */
	tmp_buf[0] = reg;
	memcpy(&tmp_buf[1], buf, cnt);

	sc = device_get_softc(dev);

	TWL_LOCK(sc);
	addr = sc->sc_subaddr_map[nsub];
	TWL_UNLOCK(sc);

	if (addr == TWL_INVALID_CHIP_ID)
		return (EIO);


	/* Setup the transfer and execute it */
	msg.slave = addr;
	msg.flags = IIC_M_WR;
	msg.len = cnt + 1;
	msg.buf = tmp_buf;

	rc = iicbus_transfer(dev, &msg, 1);
	if (rc != 0) {
		device_printf(sc->sc_dev, "iicbus write failed (adr:0x%02x, reg:0x%02x)\n",
		              addr, reg);
		return (EIO);
	}

	return (0);
}