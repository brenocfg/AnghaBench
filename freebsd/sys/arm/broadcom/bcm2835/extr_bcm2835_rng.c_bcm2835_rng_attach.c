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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sbuf {int dummy; } ;
struct bcm2835_rng_softc {int /*<<< orphan*/  sc_rngto; int /*<<< orphan*/  sc_stall_count; int /*<<< orphan*/  sc_underrun; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_rbg2x; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int ENXIO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RNG_STALL_COUNT_DEFAULT ; 
 int SBUF_AUTOEXTEND ; 
 int SBUF_INCLUDENUL ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_LONG (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct bcm2835_rng_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm2835_rng_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_rng_dump_registers (struct bcm2835_rng_softc*,struct sbuf*) ; 
 int /*<<< orphan*/  bcm2835_rng_harvest ; 
 int /*<<< orphan*/  bcm2835_rng_start (struct bcm2835_rng_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcm2835_rng_softc*) ; 
 struct bcm2835_rng_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sbuf_trim (struct sbuf*) ; 
 int /*<<< orphan*/  sysctl_bcm2835_rng_2xspeed ; 
 int /*<<< orphan*/  sysctl_bcm2835_rng_dump ; 

__attribute__((used)) static int
bcm2835_rng_attach(device_t dev)
{
	struct bcm2835_rng_softc *sc;
	struct sysctl_ctx_list *sysctl_ctx;
	struct sysctl_oid *sysctl_tree;
	int error, rid;

	error = 0;
	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_stall_count = RNG_STALL_COUNT_DEFAULT;

	/* Initialize callout */
	callout_init(&sc->sc_rngto, CALLOUT_MPSAFE);

	TUNABLE_INT_FETCH("bcmrng.2xspeed", &sc->sc_rbg2x);
	TUNABLE_INT_FETCH("bcmrng.stall_count", &sc->sc_stall_count);

	/* Allocate memory resources */
	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		bcm2835_rng_detach(dev);
		return (ENXIO);
	}

	/* Start the RNG */
	bcm2835_rng_start(sc);

	/* Dump the registers if booting verbose */
	if (bootverbose) {
		struct sbuf sb;

		(void) sbuf_new(&sb, NULL, 256,
		    SBUF_AUTOEXTEND | SBUF_INCLUDENUL);
		bcm2835_rng_dump_registers(sc, &sb);
		sbuf_trim(&sb);
		error = sbuf_finish(&sb);
		if (error == 0)
			device_printf(dev, "%s", sbuf_data(&sb));
		sbuf_delete(&sb);
	}

	sysctl_ctx = device_get_sysctl_ctx(dev);
	sysctl_tree = device_get_sysctl_tree(dev);
	SYSCTL_ADD_LONG(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "underrun", CTLFLAG_RD, &sc->sc_underrun,
	    "Number of FIFO underruns");
	SYSCTL_ADD_PROC(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "2xspeed", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    sysctl_bcm2835_rng_2xspeed, "I", "Enable RBG 2X SPEED");
	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "stall_count", CTLFLAG_RW, &sc->sc_stall_count,
	    RNG_STALL_COUNT_DEFAULT, "Number of underruns to assume RNG stall");
#ifdef BCM2835_RNG_DEBUG_REGISTERS
	SYSCTL_ADD_PROC(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree), OID_AUTO,
	    "dumpregs", CTLTYPE_STRING | CTLFLAG_RD, sc, 0,
	    sysctl_bcm2835_rng_dump, "S", "Dump RNG registers");
#endif

	/* 
	 * Schedule the initial harvesting one second from now, which should give the
	 * hardware RNG plenty of time to generate the first random bytes.
	 */
	callout_reset(&sc->sc_rngto, hz, bcm2835_rng_harvest, sc);

	return (0);
}