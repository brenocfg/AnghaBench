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
struct tda19988_softc {int /*<<< orphan*/  sc_current_page; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_addr; } ;
struct iic_msg {int member_2; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 int /*<<< orphan*/  TDA_CURPAGE_ADDR ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
tda19988_set_page(struct tda19988_softc *sc, uint8_t page)
{
	uint8_t addr = TDA_CURPAGE_ADDR;
	uint8_t cmd[2];
	int result;
	struct iic_msg msg[] = {
		{ sc->sc_addr, IIC_M_WR, 2, cmd },
	};

	cmd[0] = addr;
	cmd[1] = page;

	result = (iicbus_transfer(sc->sc_dev, msg, 1));
	if (result)
		printf("tda19988_set_page failed: %d\n", result);
	else
		sc->sc_current_page = page;

	return (result);
}