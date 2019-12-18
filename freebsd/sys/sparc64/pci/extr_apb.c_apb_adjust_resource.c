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
struct resource {int dummy; } ;
struct apb_softc {int /*<<< orphan*/  sc_memmap; int /*<<< orphan*/  sc_iomap; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  APB_IO_SCALE ; 
 int /*<<< orphan*/  APB_MEM_SCALE ; 
 int ENXIO ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  apb_checkrange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct apb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
apb_adjust_resource(device_t dev, device_t child, int type,
    struct resource *r, rman_res_t start, rman_res_t end)
{
	struct apb_softc *sc;

	sc = device_get_softc(dev);
	switch (type) {
	case SYS_RES_IOPORT:
		if (!apb_checkrange(sc->sc_iomap, APB_IO_SCALE, start, end))
			return (ENXIO);
		break;
	case SYS_RES_MEMORY:
		if (!apb_checkrange(sc->sc_memmap, APB_MEM_SCALE, start, end))
			return (ENXIO);
		break;
	}
	return (bus_generic_adjust_resource(dev, child, type, r, start, end));
}