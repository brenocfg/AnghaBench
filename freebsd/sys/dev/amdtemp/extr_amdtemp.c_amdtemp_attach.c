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
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  tn ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ich_arg; int /*<<< orphan*/  (* ich_func ) (int /*<<< orphan*/ ) ;} ;
struct amdtemp_softc {int sc_ntemps; int sc_ncores; TYPE_1__ sc_ich; int /*<<< orphan*/  sc_offset; int /*<<< orphan*/ * sc_smn; int /*<<< orphan*/  sc_gettemp; int /*<<< orphan*/  sc_flags; } ;
struct amdtemp_product {scalar_t__ amdtemp_has_cpuid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AMDID2_CMP ; 
 int AMDID_CMP_CORES ; 
 int /*<<< orphan*/  AMDTEMP_CPUID ; 
 int /*<<< orphan*/  AMDTEMP_DRAM_CONF_HIGH ; 
 int AMDTEMP_DRAM_MODE_DDR3 ; 
 int /*<<< orphan*/  AMDTEMP_FLAG_ALT_OFFSET ; 
 int /*<<< orphan*/  AMDTEMP_FLAG_CS_SWAP ; 
 int /*<<< orphan*/  AMDTEMP_FLAG_CT_10BIT ; 
 int /*<<< orphan*/  CORE0_SENSOR0 ; 
 int /*<<< orphan*/  CORE0_SENSOR1 ; 
 int /*<<< orphan*/  CORE1_SENSOR0 ; 
 int /*<<< orphan*/  CORE1_SENSOR1 ; 
 int CPUID_STEPPING ; 
 int CPUID_TO_FAMILY (int) ; 
 int CPUID_TO_MODEL (int) ; 
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int MAXCPU ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int amd_feature2 ; 
 int /*<<< orphan*/  amdtemp_gettemp ; 
 int /*<<< orphan*/  amdtemp_gettemp0f ; 
 int /*<<< orphan*/  amdtemp_gettemp15hm60h ; 
 int /*<<< orphan*/  amdtemp_gettemp17h ; 
 int /*<<< orphan*/  amdtemp_intrhook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtemp_match (int /*<<< orphan*/ ,struct amdtemp_product const**) ; 
 int /*<<< orphan*/  amdtemp_sysctl ; 
 scalar_t__ bootverbose ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int cpu_id ; 
 int cpu_procinfo2 ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct amdtemp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
amdtemp_attach(device_t dev)
{
	char tn[32];
	u_int regs[4];
	const struct amdtemp_product *product;
	struct amdtemp_softc *sc;
	struct sysctl_ctx_list *sysctlctx;
	struct sysctl_oid *sysctlnode;
	uint32_t cpuid, family, model;
	u_int bid;
	int erratum319, unit;
	bool needsmn;

	sc = device_get_softc(dev);
	erratum319 = 0;
	needsmn = false;

	if (!amdtemp_match(device_get_parent(dev), &product))
		return (ENXIO);

	cpuid = cpu_id;
	family = CPUID_TO_FAMILY(cpuid);
	model = CPUID_TO_MODEL(cpuid);

	/*
	 * This checks for the byzantine condition of running a heterogenous
	 * revision multi-socket system where the attach thread is potentially
	 * probing a remote socket's PCI device.
	 *
	 * Currently, such scenarios are unsupported on models using the SMN
	 * (because on those models, amdtemp(4) attaches to a different PCI
	 * device than the one that contains AMDTEMP_CPUID).
	 *
	 * The ancient 0x0F family of devices only supports this register from
	 * models 40h+.
	 */
	if (product->amdtemp_has_cpuid && (family > 0x0f ||
	    (family == 0x0f && model >= 0x40))) {
		cpuid = pci_read_config(device_get_parent(dev), AMDTEMP_CPUID,
		    4);
		family = CPUID_TO_FAMILY(cpuid);
		model = CPUID_TO_MODEL(cpuid);
	}

	switch (family) {
	case 0x0f:
		/*
		 * Thermaltrip Status Register
		 *
		 * - ThermSenseCoreSel
		 *
		 * Revision F & G:	0 - Core1, 1 - Core0
		 * Other:		0 - Core0, 1 - Core1
		 *
		 * - CurTmp
		 *
		 * Revision G:		bits 23-14
		 * Other:		bits 23-16
		 *
		 * XXX According to the BKDG, CurTmp, ThermSenseSel and
		 * ThermSenseCoreSel bits were introduced in Revision F
		 * but CurTmp seems working fine as early as Revision C.
		 * However, it is not clear whether ThermSenseSel and/or
		 * ThermSenseCoreSel work in undocumented cases as well.
		 * In fact, the Linux driver suggests it may not work but
		 * we just assume it does until we find otherwise.
		 *
		 * XXX According to Linux, CurTmp starts at -28C on
		 * Socket AM2 Revision G processors, which is not
		 * documented anywhere.
		 */
		if (model >= 0x40)
			sc->sc_flags |= AMDTEMP_FLAG_CS_SWAP;
		if (model >= 0x60 && model != 0xc1) {
			do_cpuid(0x80000001, regs);
			bid = (regs[1] >> 9) & 0x1f;
			switch (model) {
			case 0x68: /* Socket S1g1 */
			case 0x6c:
			case 0x7c:
				break;
			case 0x6b: /* Socket AM2 and ASB1 (2 cores) */
				if (bid != 0x0b && bid != 0x0c)
					sc->sc_flags |=
					    AMDTEMP_FLAG_ALT_OFFSET;
				break;
			case 0x6f: /* Socket AM2 and ASB1 (1 core) */
			case 0x7f:
				if (bid != 0x07 && bid != 0x09 &&
				    bid != 0x0c)
					sc->sc_flags |=
					    AMDTEMP_FLAG_ALT_OFFSET;
				break;
			default:
				sc->sc_flags |= AMDTEMP_FLAG_ALT_OFFSET;
			}
			sc->sc_flags |= AMDTEMP_FLAG_CT_10BIT;
		}

		/*
		 * There are two sensors per core.
		 */
		sc->sc_ntemps = 2;

		sc->sc_gettemp = amdtemp_gettemp0f;
		break;
	case 0x10:
		/*
		 * Erratum 319 Inaccurate Temperature Measurement
		 *
		 * http://support.amd.com/us/Processor_TechDocs/41322.pdf
		 */
		do_cpuid(0x80000001, regs);
		switch ((regs[1] >> 28) & 0xf) {
		case 0:	/* Socket F */
			erratum319 = 1;
			break;
		case 1:	/* Socket AM2+ or AM3 */
			if ((pci_cfgregread(pci_get_bus(dev),
			    pci_get_slot(dev), 2, AMDTEMP_DRAM_CONF_HIGH, 2) &
			    AMDTEMP_DRAM_MODE_DDR3) != 0 || model > 0x04 ||
			    (model == 0x04 && (cpuid & CPUID_STEPPING) >= 3))
				break;
			/* XXX 00100F42h (RB-C2) exists in both formats. */
			erratum319 = 1;
			break;
		}
		/* FALLTHROUGH */
	case 0x11:
	case 0x12:
	case 0x14:
	case 0x15:
	case 0x16:
		sc->sc_ntemps = 1;
		/*
		 * Some later (60h+) models of family 15h use a similar SMN
		 * network as family 17h.  (However, the register index differs
		 * from 17h and the decoding matches other 10h-15h models,
		 * which differ from 17h.)
		 */
		if (family == 0x15 && model >= 0x60) {
			sc->sc_gettemp = amdtemp_gettemp15hm60h;
			needsmn = true;
		} else
			sc->sc_gettemp = amdtemp_gettemp;
		break;
	case 0x17:
		sc->sc_ntemps = 1;
		sc->sc_gettemp = amdtemp_gettemp17h;
		needsmn = true;
		break;
	default:
		device_printf(dev, "Bogus family 0x%x\n", family);
		return (ENXIO);
	}

	if (needsmn) {
		sc->sc_smn = device_find_child(
		    device_get_parent(dev), "amdsmn", -1);
		if (sc->sc_smn == NULL) {
			if (bootverbose)
				device_printf(dev, "No SMN device found\n");
			return (ENXIO);
		}
	}

	/* Find number of cores per package. */
	sc->sc_ncores = (amd_feature2 & AMDID2_CMP) != 0 ?
	    (cpu_procinfo2 & AMDID_CMP_CORES) + 1 : 1;
	if (sc->sc_ncores > MAXCPU)
		return (ENXIO);

	if (erratum319)
		device_printf(dev,
		    "Erratum 319: temperature measurement may be inaccurate\n");
	if (bootverbose)
		device_printf(dev, "Found %d cores and %d sensors.\n",
		    sc->sc_ncores,
		    sc->sc_ntemps > 1 ? sc->sc_ntemps * sc->sc_ncores : 1);

	/*
	 * dev.amdtemp.N tree.
	 */
	unit = device_get_unit(dev);
	snprintf(tn, sizeof(tn), "dev.amdtemp.%d.sensor_offset", unit);
	TUNABLE_INT_FETCH(tn, &sc->sc_offset);

	sysctlctx = device_get_sysctl_ctx(dev);
	SYSCTL_ADD_INT(sysctlctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "sensor_offset", CTLFLAG_RW, &sc->sc_offset, 0,
	    "Temperature sensor offset");
	sysctlnode = SYSCTL_ADD_NODE(sysctlctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "core0", CTLFLAG_RD, 0, "Core 0");

	SYSCTL_ADD_PROC(sysctlctx,
	    SYSCTL_CHILDREN(sysctlnode),
	    OID_AUTO, "sensor0", CTLTYPE_INT | CTLFLAG_RD,
	    dev, CORE0_SENSOR0, amdtemp_sysctl, "IK",
	    "Core 0 / Sensor 0 temperature");

	if (sc->sc_ntemps > 1) {
		SYSCTL_ADD_PROC(sysctlctx,
		    SYSCTL_CHILDREN(sysctlnode),
		    OID_AUTO, "sensor1", CTLTYPE_INT | CTLFLAG_RD,
		    dev, CORE0_SENSOR1, amdtemp_sysctl, "IK",
		    "Core 0 / Sensor 1 temperature");

		if (sc->sc_ncores > 1) {
			sysctlnode = SYSCTL_ADD_NODE(sysctlctx,
			    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
			    OID_AUTO, "core1", CTLFLAG_RD, 0, "Core 1");

			SYSCTL_ADD_PROC(sysctlctx,
			    SYSCTL_CHILDREN(sysctlnode),
			    OID_AUTO, "sensor0", CTLTYPE_INT | CTLFLAG_RD,
			    dev, CORE1_SENSOR0, amdtemp_sysctl, "IK",
			    "Core 1 / Sensor 0 temperature");

			SYSCTL_ADD_PROC(sysctlctx,
			    SYSCTL_CHILDREN(sysctlnode),
			    OID_AUTO, "sensor1", CTLTYPE_INT | CTLFLAG_RD,
			    dev, CORE1_SENSOR1, amdtemp_sysctl, "IK",
			    "Core 1 / Sensor 1 temperature");
		}
	}

	/*
	 * Try to create dev.cpu sysctl entries and setup intrhook function.
	 * This is needed because the cpu driver may be loaded late on boot,
	 * after us.
	 */
	amdtemp_intrhook(dev);
	sc->sc_ich.ich_func = amdtemp_intrhook;
	sc->sc_ich.ich_arg = dev;
	if (config_intrhook_establish(&sc->sc_ich) != 0) {
		device_printf(dev, "config_intrhook_establish failed!\n");
		return (ENXIO);
	}

	return (0);
}