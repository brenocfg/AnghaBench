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
typedef  int uint16_t ;
struct tda19988_softc {scalar_t__ sc_current_page; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_addr; } ;
struct iic_msg {int member_2; int* member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 int REGADDR (int) ; 
 scalar_t__ REGPAGE (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int /*<<< orphan*/  tda19988_set_page (struct tda19988_softc*,scalar_t__) ; 

__attribute__((used)) static int
tda19988_reg_write2(struct tda19988_softc *sc, uint16_t address, uint16_t data)
{
	uint8_t cmd[3];
	int result;
	struct iic_msg msg[] = {
		{ sc->sc_addr, IIC_M_WR, 3, cmd },
	};

	cmd[0] = REGADDR(address);
	cmd[1] = (data >> 8);
	cmd[2] = (data & 0xff);

	if (sc->sc_current_page != REGPAGE(address))
		tda19988_set_page(sc, REGPAGE(address));

	result = iicbus_transfer(sc->sc_dev, msg, 1);
	if (result)
		device_printf(sc->sc_dev, "tda19988_reg_write2 failed: %d\n", result);

	return (result);
}