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
struct twl_softc {size_t* sc_subaddr_map; } ;
struct iic_msg {size_t slave; int flags; int len; size_t* buf; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EIO ; 
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int IIC_M_WR ; 
 size_t TWL_INVALID_CHIP_ID ; 
 int /*<<< orphan*/  TWL_LOCK (struct twl_softc*) ; 
 int /*<<< orphan*/  TWL_UNLOCK (struct twl_softc*) ; 
 struct twl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

int
twl_read(device_t dev, uint8_t nsub, uint8_t reg, uint8_t *buf, uint16_t cnt)
{
	struct twl_softc *sc;
	struct iic_msg msg[2];
	uint8_t addr;
	int rc;

	sc = device_get_softc(dev);

	TWL_LOCK(sc);
	addr = sc->sc_subaddr_map[nsub];
	TWL_UNLOCK(sc);

	if (addr == TWL_INVALID_CHIP_ID)
		return (EIO);


	/* Set the address to read from */
	msg[0].slave = addr;
	msg[0].flags = IIC_M_WR | IIC_M_NOSTOP;
	msg[0].len = 1;
	msg[0].buf = &reg;
	/* Read the data back */
	msg[1].slave = addr;
	msg[1].flags = IIC_M_RD;
	msg[1].len = cnt;
	msg[1].buf = buf;

	rc = iicbus_transfer(dev, msg, 2);
	if (rc != 0) {
		device_printf(dev, "iicbus read failed (adr:0x%02x, reg:0x%02x)\n",
		              addr, reg);
		return (EIO);
	}

	return (0);
}