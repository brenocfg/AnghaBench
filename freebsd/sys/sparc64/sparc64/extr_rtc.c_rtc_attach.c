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
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct resource {int dummy; } ;
struct mc146818_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_setcent; int /*<<< orphan*/  sc_getcent; int /*<<< orphan*/  sc_flag; scalar_t__ sc_year0; int /*<<< orphan*/  (* sc_mcwrite ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  sc_mcread; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MC146818_NO_CENT_ADJUST ; 
 int /*<<< orphan*/  MC_REGA ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int PC87317_APC ; 
 int /*<<< orphan*/  PC87317_APC_CADDR ; 
 int PC87317_APC_CADDR_BANK1 ; 
 int PC87317_COMMON ; 
 int PC87317_RTC_CR ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RTC_READ ; 
 int /*<<< orphan*/  RTC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct mc146818_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int mc146818_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ mc146818_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc87317_getcent ; 
 int /*<<< orphan*/  pc87317_setcent ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
rtc_attach(device_t dev)
{
	struct timespec ts;
	struct mc146818_softc *sc;
	struct resource *res;
	int ebus, error, rid;

	sc = device_get_softc(dev);

	mtx_init(&sc->sc_mtx, "rtc_mtx", NULL, MTX_SPIN);

	ebus = 0;
	if (strcmp(device_get_name(device_get_parent(dev)), "ebus") == 0)
		ebus = 1;

	rid = 0;
	res = bus_alloc_resource_any(dev, ebus ? SYS_RES_MEMORY :
	    SYS_RES_IOPORT, &rid, RF_ACTIVE);
	if (res == NULL) {
		device_printf(dev, "cannot allocate resources\n");
		error = ENXIO;
		goto fail_mtx;
	}
	sc->sc_bst = rman_get_bustag(res);
	sc->sc_bsh = rman_get_bushandle(res);

	sc->sc_mcread = RTC_READ;
	sc->sc_mcwrite = RTC_WRITE;
	/* The TOD clock year 0 is 0. */
	sc->sc_year0 = 0;
	/*
	 * For ISA use the default century get/set functions, for EBus we
	 * provide our own versions.
	 */
	sc->sc_flag = MC146818_NO_CENT_ADJUST;
	if (ebus) {
		/*
		 * Make sure the CR is at the default location (also used
		 * by Solaris).
		 */
		RTC_WRITE(dev, MC_REGA, PC87317_APC);
		RTC_WRITE(dev, PC87317_APC_CADDR, PC87317_APC_CADDR_BANK1 |
		    PC87317_RTC_CR);
		RTC_WRITE(dev, MC_REGA, PC87317_COMMON);
		sc->sc_getcent = pc87317_getcent;
		sc->sc_setcent = pc87317_setcent;
	}
	if ((error = mc146818_attach(dev)) != 0) {
		device_printf(dev, "cannot attach time of day clock\n");
		goto fail_res;
	}

	if (bootverbose) {
		if (mc146818_gettime(dev, &ts) != 0)
			device_printf(dev, "invalid time");
		else
			device_printf(dev, "current time: %ld.%09ld\n",
			    (long)ts.tv_sec, ts.tv_nsec);
	}

	return (0);

 fail_res:
	bus_release_resource(dev, ebus ? SYS_RES_MEMORY : SYS_RES_IOPORT, rid,
	    res);
 fail_mtx:
	mtx_destroy(&sc->sc_mtx);

	return (error);
}