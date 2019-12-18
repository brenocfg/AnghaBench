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
typedef  int uint32_t ;
typedef  int u_int ;
struct imx_usbmisc_softc {int /*<<< orphan*/  mmio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_read_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int,int) ; 
 struct imx_usbmisc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
imx_usbmisc_set_ctrl(device_t dev, u_int index, uint32_t bits)
{
	struct imx_usbmisc_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);
	reg = bus_read_4(sc->mmio, index * sizeof(uint32_t));
	bus_write_4(sc->mmio, index * sizeof(uint32_t), reg | bits);
}