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
typedef  int /*<<< orphan*/  uint8_t ;
struct iic_msg {int member_1; int member_2; int /*<<< orphan*/  slave; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_0; } ;
struct as3722_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_addr; } ;

/* Variables and functions */
 int EIO ; 
 int IIC_M_NOSTART ; 
 int IIC_M_WR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

int as3722_write_buf(struct as3722_softc *sc, uint8_t reg, uint8_t *buf,
    size_t size)
{
	uint8_t data[1];
	int rv;
	struct iic_msg msgs[2] = {
		{0, IIC_M_WR, 1, data},
		{0, IIC_M_WR | IIC_M_NOSTART, size, buf},
	};

	msgs[0].slave = sc->bus_addr;
	msgs[1].slave = sc->bus_addr;
	data[0] = reg;

	rv = iicbus_transfer(sc->dev, msgs, 2);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Error when writing reg 0x%02X, rv: %d\n", reg, rv);
		return (EIO);
	}
	return (0);
}