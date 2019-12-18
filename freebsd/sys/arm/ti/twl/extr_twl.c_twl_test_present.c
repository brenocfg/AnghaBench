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
struct twl_softc {int /*<<< orphan*/  sc_dev; } ;
struct iic_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IIC_M_RD ; 
 scalar_t__ iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

__attribute__((used)) static int
twl_test_present(struct twl_softc *sc, uint8_t addr)
{
	struct iic_msg msg;
	uint8_t tmp;

	/* Set the address to read from */
	msg.slave = addr;
	msg.flags = IIC_M_RD;
	msg.len = 1;
	msg.buf = &tmp;

	if (iicbus_transfer(sc->sc_dev, &msg, 1) != 0)
		return (EIO);

	return (0);
}