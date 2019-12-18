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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct jz4780_nemc_softc {int /*<<< orphan*/  simplebus_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SYS_RES_MEMORY ; 
 int bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct jz4780_nemc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int jz4780_nemc_configure_bank (struct jz4780_nemc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jz4780_nemc_decode_bank (int /*<<< orphan*/ *,struct resource*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jz4780_nemc_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *r)
{
	struct jz4780_nemc_softc *sc;
	u_int bank;
	int err;

	if (type == SYS_RES_MEMORY) {
		sc = device_get_softc(bus);

		/* Figure out on what bank device is residing */
		err = jz4780_nemc_decode_bank(&sc->simplebus_sc, r, &bank);
		if (err == 0) {
			/* Attempt to configure the bank if not done already */
			err = jz4780_nemc_configure_bank(sc, child, bank);
			if (err != 0)
				return (err);
		}
	}

	/* Call default implementation to finish the work */
	return (bus_generic_activate_resource(bus, child,
		type, rid, r));
}