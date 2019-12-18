#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ ops_pcib_sc; } ;
struct apb_softc {TYPE_2__ sc_bsc; int /*<<< orphan*/  sc_memmap; int /*<<< orphan*/  sc_iomap; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  APB_IO_SCALE ; 
 int /*<<< orphan*/  APB_MEM_SCALE ; 
 scalar_t__ RMAN_IS_DEFAULT_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  apb_checkrange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootverbose ; 
 struct resource* bus_generic_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct apb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static struct resource *
apb_alloc_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct apb_softc *sc;

	sc = device_get_softc(dev);

	/*
	 * If this is a "default" allocation against this rid, we can't work
	 * out where it's coming from (we should actually never see these) so
	 * we just have to punt.
	 */
	if (RMAN_IS_DEFAULT_RANGE(start, end)) {
		device_printf(dev, "can't decode default resource id %d for "
		    "%s, bypassing\n", *rid, device_get_nameunit(child));
		goto passup;
	}

	/*
	 * Fail the allocation for this range if it's not supported.
	 * XXX we should probably just fix up the bridge decode and
	 * soldier on.
	 */
	switch (type) {
	case SYS_RES_IOPORT:
		if (!apb_checkrange(sc->sc_iomap, APB_IO_SCALE, start, end)) {
			device_printf(dev, "device %s requested unsupported "
			    "I/O range 0x%jx-0x%jx\n",
			    device_get_nameunit(child), start, end);
			return (NULL);
		}
		if (bootverbose)
			device_printf(sc->sc_bsc.ops_pcib_sc.dev, "device "
			    "%s requested decoded I/O range 0x%jx-0x%jx\n",
			    device_get_nameunit(child), start, end);
		break;
	case SYS_RES_MEMORY:
		if (!apb_checkrange(sc->sc_memmap, APB_MEM_SCALE, start,
		    end)) {
			device_printf(dev, "device %s requested unsupported "
			    "memory range 0x%jx-0x%jx\n",
			    device_get_nameunit(child), start, end);
			return (NULL);
		}
		if (bootverbose)
			device_printf(sc->sc_bsc.ops_pcib_sc.dev, "device "
			    "%s requested decoded memory range 0x%jx-0x%jx\n",
			    device_get_nameunit(child), start, end);
		break;
	}

 passup:
	/*
	 * Bridge is OK decoding this resource, so pass it up.
	 */
	return (bus_generic_alloc_resource(dev, child, type, rid, start, end,
	    count, flags));
}