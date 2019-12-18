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
struct jz4780_efuse_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  data; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_efuse_softc*,int /*<<< orphan*/ ,int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  JZ_EFUCFG ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jz4780_efuse_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jz4780_efuse_read (struct jz4780_efuse_softc*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jz4780_efuse_spec ; 
 int /*<<< orphan*/  jz4780_efuse_update_kenv (struct jz4780_efuse_softc*) ; 

__attribute__((used)) static int
jz4780_efuse_attach(device_t dev)
{
	struct jz4780_efuse_softc *sc;

 	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, jz4780_efuse_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	/*
	 * Default RD_STROBE to 4 h2clk cycles, should already be set to 4 by  reset
	 * but configure it anyway.
	 */
	CSR_WRITE_4(sc, JZ_EFUCFG, 0x00040000);

	/* Read user-id segment */
	jz4780_efuse_read(sc, 0x18, &sc->data, sizeof(sc->data));

	/*
	 * Set resource hints for the dme device to discover its
	 * MAC address, if not set already.
	 */
	jz4780_efuse_update_kenv(sc);

	/* Resource conflicts with NEMC, release early */
	bus_release_resources(dev, jz4780_efuse_spec, sc->res);
	return (0);
}