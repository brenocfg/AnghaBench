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
typedef  int /*<<< orphan*/  uint16_t ;
struct rsu_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92S_EFUSE_CTRL ; 
 int /*<<< orphan*/  R92S_EFUSE_CTRL_ADDR ; 
 int /*<<< orphan*/  R92S_EFUSE_CTRL_DATA ; 
 int R92S_EFUSE_CTRL_VALID ; 
 int RW (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_ms_delay (struct rsu_softc*,int) ; 
 int rsu_read_4 (struct rsu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_write_4 (struct rsu_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
rsu_efuse_read_1(struct rsu_softc *sc, uint16_t addr)
{
	uint32_t reg;
	int ntries;

	reg = rsu_read_4(sc, R92S_EFUSE_CTRL);
	reg = RW(reg, R92S_EFUSE_CTRL_ADDR, addr);
	reg &= ~R92S_EFUSE_CTRL_VALID;
	rsu_write_4(sc, R92S_EFUSE_CTRL, reg);
	/* Wait for read operation to complete. */
	for (ntries = 0; ntries < 100; ntries++) {
		reg = rsu_read_4(sc, R92S_EFUSE_CTRL);
		if (reg & R92S_EFUSE_CTRL_VALID)
			return (MS(reg, R92S_EFUSE_CTRL_DATA));
		rsu_ms_delay(sc, 1);
	}
	device_printf(sc->sc_dev,
	    "could not read efuse byte at address 0x%x\n", addr);
	return (0xff);
}