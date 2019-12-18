#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct apm_softc* ah_arg; int /*<<< orphan*/  ah_fun; } ;
struct TYPE_10__ {int eax; } ;
struct TYPE_8__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct TYPE_9__ {TYPE_2__ data; TYPE_1__ code16; } ;
struct TYPE_11__ {TYPE_4__ r; TYPE_3__ seg; int /*<<< orphan*/  entry; } ;
struct apm_softc {int initialized; int always_halt_cpu; int slow_idle_cpu; int minorversion; int majorversion; TYPE_6__ sc_resume; TYPE_6__ sc_suspend; scalar_t__ running; scalar_t__ suspending; TYPE_5__ bios; scalar_t__ disengaged; int /*<<< orphan*/  intversion; scalar_t__ disabled; scalar_t__ active; int /*<<< orphan*/  cv; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  APMDEV_CTL ; 
 int /*<<< orphan*/  APMDEV_NORMAL ; 
 int /*<<< orphan*/  APM_DPRINT (char*,...) ; 
 int /*<<< orphan*/  APM_HOOK_RESUME ; 
 int /*<<< orphan*/  APM_HOOK_SUSPEND ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  INTVERSION (int,int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  POWER_PM_TYPE_APM ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  apm_cdevsw ; 
 int /*<<< orphan*/  apm_debug ; 
 scalar_t__ apm_driver_version (int) ; 
 scalar_t__ apm_enable_disable_pm (int) ; 
 scalar_t__ apm_engage_disengage_pm (int) ; 
 int /*<<< orphan*/  apm_hook_establish (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  apm_pm_func ; 
 int /*<<< orphan*/  apm_power_off ; 
 int /*<<< orphan*/  apm_rtc_resume ; 
 int /*<<< orphan*/  apm_rtc_suspend ; 
 struct apm_softc apm_softc ; 
 int apm_version ; 
 int atrtcclock_disable ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  getenv_int (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_enabled (int) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_pm_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct apm_softc*) ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static int
apm_attach(device_t dev)
{
	struct apm_softc	*sc = &apm_softc;
	int			drv_version;

	mtx_init(&sc->mtx, device_get_nameunit(dev), "apm", MTX_DEF);
	cv_init(&sc->cv, "cbb cv");

	if (device_get_flags(dev) & 0x20)
		atrtcclock_disable = 1;

	sc->initialized = 0;

	/* Must be externally enabled */
	sc->active = 0;

	/* Always call HLT in idle loop */
	sc->always_halt_cpu = 1;

	getenv_int("debug.apm_debug", &apm_debug);

	/* print bootstrap messages */
	APM_DPRINT("apm: APM BIOS version %04lx\n",  apm_version);
	APM_DPRINT("apm: Code16 0x%08x, Data 0x%08x\n",
	    sc->bios.seg.code16.base, sc->bios.seg.data.base);
	APM_DPRINT("apm: Code entry 0x%08x, Idling CPU %s, Management %s\n",
	    sc->bios.entry, is_enabled(sc->slow_idle_cpu),
	    is_enabled(!sc->disabled));
	APM_DPRINT("apm: CS_limit=0x%x, DS_limit=0x%x\n",
	    sc->bios.seg.code16.limit, sc->bios.seg.data.limit);

	/*
         * In one test, apm bios version was 1.02; an attempt to register
         * a 1.04 driver resulted in a 1.00 connection!  Registering a
         * 1.02 driver resulted in a 1.02 connection.
         */
	drv_version = apm_version > 0x102 ? 0x102 : apm_version;
	for (; drv_version > 0x100; drv_version--)
		if (apm_driver_version(drv_version) == 0)
			break;
	sc->minorversion = ((drv_version & 0x00f0) >>  4) * 10 +
		((drv_version & 0x000f) >> 0);
	sc->majorversion = ((drv_version & 0xf000) >> 12) * 10 +
		((apm_version & 0x0f00) >> 8);

	sc->intversion = INTVERSION(sc->majorversion, sc->minorversion);

	if (sc->intversion >= INTVERSION(1, 1))
		APM_DPRINT("apm: Engaged control %s\n", is_enabled(!sc->disengaged));
	device_printf(dev, "found APM BIOS v%ld.%ld, connected at v%d.%d\n",
	       ((apm_version & 0xf000) >> 12) * 10 + ((apm_version & 0x0f00) >> 8),
	       ((apm_version & 0x00f0) >> 4) * 10 + ((apm_version & 0x000f) >> 0),
	       sc->majorversion, sc->minorversion);


	APM_DPRINT("apm: Slow Idling CPU %s\n", is_enabled(sc->slow_idle_cpu));
	/* enable power management */
	if (sc->disabled) {
		if (apm_enable_disable_pm(1)) {
			APM_DPRINT("apm: *Warning* enable function failed! [%x]\n",
			    (sc->bios.r.eax >> 8) & 0xff);
		}
	}

	/* engage power managment (APM 1.1 or later) */
	if (sc->intversion >= INTVERSION(1, 1) && sc->disengaged) {
		if (apm_engage_disengage_pm(1)) {
			APM_DPRINT("apm: *Warning* engage function failed err=[%x]",
			    (sc->bios.r.eax >> 8) & 0xff);
			APM_DPRINT(" (Docked or using external power?).\n");
		}
	}

	/* Power the system off using APM */
	EVENTHANDLER_REGISTER(shutdown_final, apm_power_off, NULL,
			      SHUTDOWN_PRI_LAST);

	/* Register APM again to pass the correct argument of pm_func. */
	power_pm_register(POWER_PM_TYPE_APM, apm_pm_func, sc);

	sc->initialized = 1;
	sc->suspending = 0;
	sc->running = 0;

	make_dev(&apm_cdevsw, APMDEV_NORMAL,
	    UID_ROOT, GID_OPERATOR, 0664, "apm");
	make_dev(&apm_cdevsw, APMDEV_CTL,
	    UID_ROOT, GID_OPERATOR, 0660, "apmctl");

	sc->sc_suspend.ah_fun = apm_rtc_suspend;
	sc->sc_suspend.ah_arg = sc;
	apm_hook_establish(APM_HOOK_SUSPEND, &sc->sc_suspend);

	sc->sc_resume.ah_fun = apm_rtc_resume;
	sc->sc_resume.ah_arg = sc;
	apm_hook_establish(APM_HOOK_RESUME, &sc->sc_resume);

	return 0;
}