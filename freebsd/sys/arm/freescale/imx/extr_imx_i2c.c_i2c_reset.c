#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct i2c_softc {int byte_time_sbt; int /*<<< orphan*/  iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {size_t divisor; scalar_t__ regcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_DEBUGF (struct i2c_softc*,int,char*) ; 
 int /*<<< orphan*/  I2C_CONTROL_REG ; 
 int /*<<< orphan*/  I2C_FDR_REG ; 
 int /*<<< orphan*/  I2C_STATUS_REG ; 
 size_t IICBUS_GET_FREQUENCY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SBT_1US ; 
 TYPE_1__* clkdiv_table ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t howmany (size_t,size_t) ; 
 int i2c_recover_bus (struct i2c_softc*) ; 
 int /*<<< orphan*/  i2c_write_reg (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 size_t imx_ccm_ipg_hz () ; 
 size_t nitems (TYPE_1__*) ; 

__attribute__((used)) static int
i2c_reset(device_t dev, u_char speed, u_char addr, u_char *oldadr)
{
	struct i2c_softc *sc;
	u_int busfreq, div, i, ipgfreq;

	sc = device_get_softc(dev);

	DEVICE_DEBUGF(sc, 1, "reset\n");

	/*
	 * Look up the divisor that gives the nearest speed that doesn't exceed
	 * the configured value for the bus.
	 */
	ipgfreq = imx_ccm_ipg_hz();
	busfreq = IICBUS_GET_FREQUENCY(sc->iicbus, speed);
	div = howmany(ipgfreq, busfreq);
	for (i = 0; i < nitems(clkdiv_table); i++) {
		if (clkdiv_table[i].divisor >= div)
			break;
	}

	/*
	 * Calculate roughly how long it will take to transfer a byte (which
	 * requires 9 clock cycles) at the new bus speed.  This value is used to
	 * pause() while waiting for transfer-complete.  With a 66MHz IPG clock
	 * and the actual i2c bus speeds that leads to, for nominal 100KHz and
	 * 400KHz bus speeds the transfer times are roughly 104uS and 22uS.
	 */
	busfreq = ipgfreq / clkdiv_table[i].divisor;
	sc->byte_time_sbt = SBT_1US * (9000000 / busfreq);

	/*
	 * Disable the controller (do the reset), and set the new clock divisor.
	 */
	i2c_write_reg(sc, I2C_STATUS_REG, 0x0);
	i2c_write_reg(sc, I2C_CONTROL_REG, 0x0);
	i2c_write_reg(sc, I2C_FDR_REG, (uint8_t)clkdiv_table[i].regcode);

	/*
	 * Now that the controller is idle, perform bus recovery.  If the bus
	 * isn't hung, this a fairly fast no-op.
	 */
	return (i2c_recover_bus(sc));
}