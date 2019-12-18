#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {char* rm_descr; int /*<<< orphan*/  rm_type; int /*<<< orphan*/  rm_end; scalar_t__ rm_start; } ;
struct chipc_softc {int /*<<< orphan*/  dev; TYPE_1__ mem_rman; } ;
typedef  int /*<<< orphan*/  bhnd_port_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 size_t bhnd_get_port_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_port_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipc_free_rman (struct chipc_softc*) ; 
 int chipc_rman_init_regions (struct chipc_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 
 int rman_init (TYPE_1__*) ; 

__attribute__((used)) static int
chipc_init_rman(struct chipc_softc *sc)
{
	u_int	num_ports;
	int	error;

	/* Port types for which we'll register chipc_region mappings */
	bhnd_port_type types[] = {
	    BHND_PORT_DEVICE
	};

	/* Initialize resource manager */
	sc->mem_rman.rm_start = 0;
	sc->mem_rman.rm_end = BUS_SPACE_MAXADDR;
	sc->mem_rman.rm_type = RMAN_ARRAY;
	sc->mem_rman.rm_descr = "ChipCommon Device Memory";
	if ((error = rman_init(&sc->mem_rman))) {
		device_printf(sc->dev, "could not initialize mem_rman: %d\n",
		    error);
		return (error);
	}

	/* Populate per-port-region state */
	for (u_int i = 0; i < nitems(types); i++) {
		num_ports = bhnd_get_port_count(sc->dev, types[i]);
		for (u_int port = 0; port < num_ports; port++) {
			error = chipc_rman_init_regions(sc, types[i], port);
			if (error) {
				device_printf(sc->dev,
				    "region init failed for %s%u: %d\n",
				     bhnd_port_type_name(types[i]), port,
				     error);

				goto failed;
			}
		}
	}

	return (0);

failed:
	chipc_free_rman(sc);
	return (error);
}