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
typedef  int uint64_t ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct coretemp_softc {int sc_tjmax; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORETEMP_DELTA ; 
 int /*<<< orphan*/  CORETEMP_RESOLUTION ; 
 int /*<<< orphan*/  CORETEMP_TEMP ; 
 int /*<<< orphan*/  CORETEMP_TJMAX ; 
 int CPUID_STEPPING ; 
 int CPUID_TO_MODEL (int) ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  MSR_BIOS_SIGN ; 
 int /*<<< orphan*/  MSR_IA32_EXT_CONFIG ; 
 int /*<<< orphan*/  MSR_IA32_TEMPERATURE_TARGET ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  coretemp_get_val_sysctl ; 
 int /*<<< orphan*/  coretemp_throttle_log_sysctl ; 
 int cpu_id ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct coretemp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int rdmsr_safe (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
coretemp_attach(device_t dev)
{
	struct coretemp_softc *sc = device_get_softc(dev);
	device_t pdev;
	uint64_t msr;
	int cpu_model, cpu_stepping;
	int ret, tjtarget;
	struct sysctl_oid *oid;
	struct sysctl_ctx_list *ctx;

	sc->sc_dev = dev;
	pdev = device_get_parent(dev);
	cpu_model = CPUID_TO_MODEL(cpu_id);
	cpu_stepping = cpu_id & CPUID_STEPPING;

	/*
	 * Some CPUs, namely the PIII, don't have thermal sensors, but
	 * report them when the CPUID check is performed in
	 * coretemp_identify(). This leads to a later GPF when the sensor
	 * is queried via a MSR, so we stop here.
	 */
	if (cpu_model < 0xe)
		return (ENXIO);

#if 0 /*
       * XXXrpaulo: I have this CPU model and when it returns from C3
       * coretemp continues to function properly.
       */
	 
	/*
	 * Check for errata AE18.
	 * "Processor Digital Thermal Sensor (DTS) Readout stops
	 *  updating upon returning from C3/C4 state."
	 *
	 * Adapted from the Linux coretemp driver.
	 */
	if (cpu_model == 0xe && cpu_stepping < 0xc) {
		msr = rdmsr(MSR_BIOS_SIGN);
		msr = msr >> 32;
		if (msr < 0x39) {
			device_printf(dev, "not supported (Intel errata "
			    "AE18), try updating your BIOS\n");
			return (ENXIO);
		}
	}
#endif

	/*
	 * Use 100C as the initial value.
	 */
	sc->sc_tjmax = 100;

	if ((cpu_model == 0xf && cpu_stepping >= 2) || cpu_model == 0xe) {
		/*
		 * On some Core 2 CPUs, there's an undocumented MSR that
		 * can tell us if Tj(max) is 100 or 85.
		 *
		 * The if-clause for CPUs having the MSR_IA32_EXT_CONFIG was adapted
		 * from the Linux coretemp driver.
		 */
		msr = rdmsr(MSR_IA32_EXT_CONFIG);
		if (msr & (1 << 30))
			sc->sc_tjmax = 85;
	} else if (cpu_model == 0x17) {
		switch (cpu_stepping) {
		case 0x6:	/* Mobile Core 2 Duo */
			sc->sc_tjmax = 105;
			break;
		default:	/* Unknown stepping */
			break;
		}
	} else if (cpu_model == 0x1c) {
		switch (cpu_stepping) {
		case 0xa:	/* 45nm Atom D400, N400 and D500 series */
			sc->sc_tjmax = 100;
			break;
		default:
			sc->sc_tjmax = 90;
			break;
		}
	} else {
		/*
		 * Attempt to get Tj(max) from MSR IA32_TEMPERATURE_TARGET.
		 *
		 * This method is described in Intel white paper "CPU
		 * Monitoring With DTS/PECI". (#322683)
		 */
		ret = rdmsr_safe(MSR_IA32_TEMPERATURE_TARGET, &msr);
		if (ret == 0) {
			tjtarget = (msr >> 16) & 0xff;

			/*
			 * On earlier generation of processors, the value
			 * obtained from IA32_TEMPERATURE_TARGET register is
			 * an offset that needs to be summed with a model
			 * specific base.  It is however not clear what
			 * these numbers are, with the publicly available
			 * documents from Intel.
			 *
			 * For now, we consider [70, 110]C range, as
			 * described in #322683, as "reasonable" and accept
			 * these values whenever the MSR is available for
			 * read, regardless the CPU model.
			 */
			if (tjtarget >= 70 && tjtarget <= 110)
				sc->sc_tjmax = tjtarget;
			else
				device_printf(dev, "Tj(target) value %d "
				    "does not seem right.\n", tjtarget);
		} else
			device_printf(dev, "Can not get Tj(target) "
			    "from your CPU, using 100C.\n");
	}

	if (bootverbose)
		device_printf(dev, "Setting TjMax=%d\n", sc->sc_tjmax);

	ctx = device_get_sysctl_ctx(dev);

	oid = SYSCTL_ADD_NODE(ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(pdev)), OID_AUTO,
	    "coretemp", CTLFLAG_RD, NULL, "Per-CPU thermal information");

	/*
	 * Add the MIBs to dev.cpu.N and dev.cpu.N.coretemp.
	 */
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(device_get_sysctl_tree(pdev)),
	    OID_AUTO, "temperature", CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE,
	    dev, CORETEMP_TEMP, coretemp_get_val_sysctl, "IK",
	    "Current temperature");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(oid), OID_AUTO, "delta",
	    CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, dev, CORETEMP_DELTA,
	    coretemp_get_val_sysctl, "I",
	    "Delta between TCC activation and current temperature");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(oid), OID_AUTO, "resolution",
	    CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, dev, CORETEMP_RESOLUTION,
	    coretemp_get_val_sysctl, "I",
	    "Resolution of CPU thermal sensor");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(oid), OID_AUTO, "tjmax",
	    CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, dev, CORETEMP_TJMAX,
	    coretemp_get_val_sysctl, "IK",
	    "TCC activation temperature");
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "throttle_log", CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_MPSAFE, dev, 0,
	    coretemp_throttle_log_sysctl, "I",
	    "Set to 1 if the thermal sensor has tripped");

	return (0);
}