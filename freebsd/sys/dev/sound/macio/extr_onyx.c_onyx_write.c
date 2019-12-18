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
typedef  int u_int ;
struct onyx_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_addr; } ;
struct iic_msg {int len; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 int /*<<< orphan*/  iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

__attribute__((used)) static int
onyx_write(struct onyx_softc *sc, uint8_t reg, const uint8_t value)
{
	u_int size;
	uint8_t buf[16];

	struct iic_msg msg[] = {
		{ sc->sc_addr, IIC_M_WR, 0, buf }
	};

	size = 1;
	msg[0].len = size + 1;
	buf[0] = reg;
	buf[1] = value;

	iicbus_transfer(sc->sc_dev, msg, 1);

	return (0);
}