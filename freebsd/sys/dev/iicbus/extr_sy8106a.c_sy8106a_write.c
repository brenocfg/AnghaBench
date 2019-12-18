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
struct sy8106a_softc {int /*<<< orphan*/  addr; } ;
struct iic_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  slave; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 struct sy8106a_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

__attribute__((used)) static int
sy8106a_write(device_t dev, uint8_t reg, uint8_t val)
{
	struct sy8106a_softc *sc;
	struct iic_msg msg;
	uint8_t buffer[2];

	sc = device_get_softc(dev);

	buffer[0] = reg;
	buffer[1] = val;

	msg.slave = sc->addr;
	msg.flags = IIC_M_WR;
	msg.len = 2;
	msg.buf = buffer;

	return (iicbus_transfer(dev, &msg, 1));
}