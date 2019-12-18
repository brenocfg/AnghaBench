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
typedef  int /*<<< orphan*/  u_char ;
struct iicbus_softc {int strict; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iicbus_softc* IICBUS_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIC_FASTEST ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 scalar_t__ iic_probe_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_init_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int,char*,int*) ; 

__attribute__((used)) static int
iicbus_attach(device_t dev)
{
#if SCAN_IICBUS
	unsigned char addr;
#endif
	struct iicbus_softc *sc = IICBUS_SOFTC(dev);
	int strict;

	sc->dev = dev;
	mtx_init(&sc->lock, "iicbus", NULL, MTX_DEF);
	iicbus_init_frequency(dev, 0);
	iicbus_reset(dev, IIC_FASTEST, 0, NULL);
	if (resource_int_value(device_get_name(dev),
		device_get_unit(dev), "strict", &strict) == 0)
		sc->strict = strict;
	else
		sc->strict = 1;

	/* device probing is meaningless since the bus is supposed to be
	 * hot-plug. Moreover, some I2C chips do not appreciate random
	 * accesses like stop after start to fast, reads for less than
	 * x bytes...
	 */
#if SCAN_IICBUS
	printf("Probing for devices on iicbus%d:", device_get_unit(dev));

	/* probe any devices */
	for (addr = 16; addr < 240; addr++) {
		if (iic_probe_device(dev, (u_char)addr)) {
			printf(" <%x>", addr);
		}
	}
	printf("\n");
#endif
	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	bus_generic_attach(dev);
        return (0);
}