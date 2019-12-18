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
typedef  scalar_t__ uint32_t ;
struct iic_msg {int member_0; int member_2; int* member_3; int /*<<< orphan*/  member_1; } ;
struct dwc_hdmi_softc {int* sc_edid; scalar_t__ sc_edid_len; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * (* sc_get_i2c_dev ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int ENXIO ; 
 int I2C_DDC_ADDR ; 
 int I2C_DDC_SEGADDR ; 
 int /*<<< orphan*/  IIC_INTRWAIT ; 
 int /*<<< orphan*/  IIC_M_RD ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_transfer (int /*<<< orphan*/ *,struct iic_msg*,int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdmi_edid_read(struct dwc_hdmi_softc *sc, int block, uint8_t **edid,
    uint32_t *edid_len)
{
	device_t i2c_dev;
	int result;
	uint8_t addr = block & 1 ? EDID_LENGTH : 0;
	uint8_t segment = block >> 1;
	struct iic_msg msg[] = {
		{ I2C_DDC_SEGADDR, IIC_M_WR, 1, &segment },
		{ I2C_DDC_ADDR, IIC_M_WR, 1, &addr },
		{ I2C_DDC_ADDR, IIC_M_RD, EDID_LENGTH, sc->sc_edid }
	};

	*edid = NULL;
	*edid_len = 0;
	i2c_dev = NULL;

	if (sc->sc_get_i2c_dev != NULL)
		i2c_dev = sc->sc_get_i2c_dev(sc->sc_dev);
	if (!i2c_dev) {
		device_printf(sc->sc_dev, "no DDC device found\n");
		return (ENXIO);
	}

	if (bootverbose)
		device_printf(sc->sc_dev,
		    "reading EDID from %s, block %d, addr %02x\n",
		    device_get_nameunit(i2c_dev), block, I2C_DDC_ADDR/2);

	result = iicbus_request_bus(i2c_dev, sc->sc_dev, IIC_INTRWAIT);

	if (result) {
		device_printf(sc->sc_dev, "failed to request i2c bus: %d\n", result);
		return (result);
	}

	result = iicbus_transfer(i2c_dev, msg, 3);
	iicbus_release_bus(i2c_dev, sc->sc_dev);

	if (result) {
		device_printf(sc->sc_dev, "i2c transfer failed: %d\n", result);
		return (result);
	} else {
		*edid_len = sc->sc_edid_len;
		*edid = sc->sc_edid;
	}

	return (result);
}