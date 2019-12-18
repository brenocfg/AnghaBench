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
struct sysctl_oid {int dummy; } ;
struct TYPE_2__ {struct bcm2835_cpufreq_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct bcm2835_cpufreq_softc {int arm_max_freq; int arm_min_freq; int core_max_freq; int core_min_freq; int sdram_max_freq; int sdram_min_freq; TYPE_1__ init_hook; scalar_t__ min_voltage_core; scalar_t__ max_voltage_core; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLFLAG_WR ; 
 int CTLTYPE_INT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct bcm2835_cpufreq_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw ; 
 int /*<<< orphan*/  bcm2835_cpufreq_init ; 
 int /*<<< orphan*/  bcm2835_sysctl_ctx ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 struct bcm2835_cpufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_arm_freq ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_core_freq ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_sdram_freq ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_temperature ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_turbo ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_voltage_core ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_voltage_sdram ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_voltage_sdram_c ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_voltage_sdram_i ; 
 int /*<<< orphan*/  sysctl_bcm2835_cpufreq_voltage_sdram_p ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_sema ; 

__attribute__((used)) static int
bcm2835_cpufreq_attach(device_t dev)
{
	struct bcm2835_cpufreq_softc *sc;
	struct sysctl_oid *oid;

	/* set self dev */
	sc = device_get_softc(dev);
	sc->dev = dev;

	/* initial values */
	sc->arm_max_freq = -1;
	sc->arm_min_freq = -1;
	sc->core_max_freq = -1;
	sc->core_min_freq = -1;
	sc->sdram_max_freq = -1;
	sc->sdram_min_freq = -1;
	sc->max_voltage_core = 0;
	sc->min_voltage_core = 0;

	/* setup sysctl at first device */
	if (device_get_unit(dev) == 0) {
		sysctl_ctx_init(&bcm2835_sysctl_ctx);
		/* create node for hw.cpufreq */
		oid = SYSCTL_ADD_NODE(&bcm2835_sysctl_ctx,
		    SYSCTL_STATIC_CHILDREN(_hw), OID_AUTO, "cpufreq",
		    CTLFLAG_RD, NULL, "");

		/* Frequency (Hz) */
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "arm_freq", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
		    sysctl_bcm2835_cpufreq_arm_freq, "IU",
		    "ARM frequency (Hz)");
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "core_freq", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
		    sysctl_bcm2835_cpufreq_core_freq, "IU",
		    "Core frequency (Hz)");
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "sdram_freq", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
		    sysctl_bcm2835_cpufreq_sdram_freq, "IU",
		    "SDRAM frequency (Hz)");

		/* Turbo state */
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "turbo", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
		    sysctl_bcm2835_cpufreq_turbo, "IU",
		    "Disables dynamic clocking");

		/* Voltage (offset from 1.2V in units of 0.025V) */
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "voltage_core", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
		    sysctl_bcm2835_cpufreq_voltage_core, "I",
		    "ARM/GPU core voltage"
		    "(offset from 1.2V in units of 0.025V)");
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "voltage_sdram", CTLTYPE_INT | CTLFLAG_WR, sc,
		    0, sysctl_bcm2835_cpufreq_voltage_sdram, "I",
		    "SDRAM voltage (offset from 1.2V in units of 0.025V)");

		/* Voltage individual SDRAM */
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "voltage_sdram_c", CTLTYPE_INT | CTLFLAG_RW, sc,
		    0, sysctl_bcm2835_cpufreq_voltage_sdram_c, "I",
		    "SDRAM controller voltage"
		    "(offset from 1.2V in units of 0.025V)");
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "voltage_sdram_i", CTLTYPE_INT | CTLFLAG_RW, sc,
		    0, sysctl_bcm2835_cpufreq_voltage_sdram_i, "I",
		    "SDRAM I/O voltage (offset from 1.2V in units of 0.025V)");
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "voltage_sdram_p", CTLTYPE_INT | CTLFLAG_RW, sc,
		    0, sysctl_bcm2835_cpufreq_voltage_sdram_p, "I",
		    "SDRAM phy voltage (offset from 1.2V in units of 0.025V)");

		/* Temperature */
		SYSCTL_ADD_PROC(&bcm2835_sysctl_ctx, SYSCTL_CHILDREN(oid),
		    OID_AUTO, "temperature", CTLTYPE_INT | CTLFLAG_RD, sc, 0,
		    sysctl_bcm2835_cpufreq_temperature, "I",
		    "SoC temperature (thousandths of a degree C)");
	}

	/* ARM->VC lock */
	sema_init(&vc_sema, 1, "vcsema");

	/* register callback for using mbox when interrupts are enabled */
	sc->init_hook.ich_func = bcm2835_cpufreq_init;
	sc->init_hook.ich_arg = sc;

	if (config_intrhook_establish(&sc->init_hook) != 0) {
		device_printf(dev, "config_intrhook_establish failed\n");
		return (ENOMEM);
	}

	/* this device is controlled by cpufreq(4) */
	cpufreq_register(dev);

	return (0);
}