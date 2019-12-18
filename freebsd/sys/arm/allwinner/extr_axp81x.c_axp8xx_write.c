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
struct iic_msg {int len; int /*<<< orphan*/ * buf; void* flags; int /*<<< orphan*/  slave; } ;
struct axp8xx_softc {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* IIC_M_WR ; 
 struct axp8xx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

__attribute__((used)) static int
axp8xx_write(device_t dev, uint8_t reg, uint8_t val)
{
	struct axp8xx_softc *sc;
	struct iic_msg msg[2];

	sc = device_get_softc(dev);

	msg[0].slave = sc->addr;
	msg[0].flags = IIC_M_WR;
	msg[0].len = 1;
	msg[0].buf = &reg;

	msg[1].slave = sc->addr;
	msg[1].flags = IIC_M_WR;
	msg[1].len = 1;
	msg[1].buf = &val;

	return (iicbus_transfer(dev, msg, 2));
}