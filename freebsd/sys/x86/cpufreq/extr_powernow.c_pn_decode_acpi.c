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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct powernow_state {size_t fid; int freq; int /*<<< orphan*/  power; int /*<<< orphan*/  vid; } ;
struct pn_softc {int errata; int pn_type; int powernow_max_states; int fsb; struct powernow_state* powernow_states; int /*<<< orphan*/  low; int /*<<< orphan*/  irt; int /*<<< orphan*/  rvo; int /*<<< orphan*/  pll; int /*<<< orphan*/  mvs; int /*<<< orphan*/  vst; scalar_t__ sgtc; } ;
struct cf_setting {int freq; int /*<<< orphan*/  power; scalar_t__* spec; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int A0_ERRATA ; 
 size_t ACPI_PN7_CTRL_TO_FID (scalar_t__) ; 
 scalar_t__ ACPI_PN7_CTRL_TO_SGTC (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PN7_CTRL_TO_VID (scalar_t__) ; 
 size_t ACPI_PN8_CTRL_TO_FID (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PN8_CTRL_TO_IRT (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PN8_CTRL_TO_MVS (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PN8_CTRL_TO_PLL (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PN8_CTRL_TO_RVO (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PN8_CTRL_TO_VID (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_PN8_CTRL_TO_VST (scalar_t__) ; 
 int CPUFREQ_DRV_SETTINGS (int /*<<< orphan*/ *,struct cf_setting*,int*) ; 
 int CPUFREQ_DRV_TYPE (int /*<<< orphan*/ *,int*) ; 
 int CPUFREQ_FLAG_INFO_ONLY ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MSR_AMDK7_FIDVID_STATUS ; 
 size_t PN7_STA_MFID (int /*<<< orphan*/ ) ; 
#define  PN7_TYPE 129 
#define  PN8_TYPE 128 
 int POWERNOW_MAX_STATES ; 
 size_t PX_SPEC_CONTROL ; 
 struct pn_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int /*<<< orphan*/  memcpy (struct powernow_state*,struct powernow_state*,int) ; 
 int* pn7_fid_to_mult ; 
 int* pn8_fid_to_mult ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pn_decode_acpi(device_t dev, device_t perf_dev)
{
	int i, j, n;
	uint64_t status;
	uint32_t ctrl;
	u_int cpuid;
	u_int regs[4];
	struct pn_softc *sc;
	struct powernow_state state;
	struct cf_setting sets[POWERNOW_MAX_STATES];
	int count = POWERNOW_MAX_STATES;
	int type;
	int rv;

	if (perf_dev == NULL)
		return (ENXIO);

	rv = CPUFREQ_DRV_SETTINGS(perf_dev, sets, &count);
	if (rv)
		return (ENXIO);
	rv = CPUFREQ_DRV_TYPE(perf_dev, &type);
	if (rv || (type & CPUFREQ_FLAG_INFO_ONLY) == 0)
		return (ENXIO);

	sc = device_get_softc(dev);

	do_cpuid(0x80000001, regs);
	cpuid = regs[0];
	if ((cpuid & 0xfff) == 0x760)
		sc->errata |= A0_ERRATA;

	ctrl = 0;
	sc->sgtc = 0;
	for (n = 0, i = 0; i < count; ++i) {
		ctrl = sets[i].spec[PX_SPEC_CONTROL];
		switch (sc->pn_type) {
		case PN7_TYPE:
			state.fid = ACPI_PN7_CTRL_TO_FID(ctrl);
			state.vid = ACPI_PN7_CTRL_TO_VID(ctrl);
			if ((sc->errata & A0_ERRATA) &&
			    (pn7_fid_to_mult[state.fid] % 10) == 5)
				continue;
			break;
		case PN8_TYPE:
			state.fid = ACPI_PN8_CTRL_TO_FID(ctrl);
			state.vid = ACPI_PN8_CTRL_TO_VID(ctrl);
			break;
		}
		state.freq = sets[i].freq * 1000;
		state.power = sets[i].power;

		j = n;
		while (j > 0 && sc->powernow_states[j - 1].freq < state.freq) {
			memcpy(&sc->powernow_states[j],
			    &sc->powernow_states[j - 1],
			    sizeof(struct powernow_state));
			--j;
		}
		memcpy(&sc->powernow_states[j], &state,
		    sizeof(struct powernow_state));
		++n;
	}

	sc->powernow_max_states = n;
	state = sc->powernow_states[0];
	status = rdmsr(MSR_AMDK7_FIDVID_STATUS);

	switch (sc->pn_type) {
	case PN7_TYPE:
		sc->sgtc = ACPI_PN7_CTRL_TO_SGTC(ctrl);
		/*
		 * XXX Some bios forget the max frequency!
		 * This maybe indicates we have the wrong tables.  Therefore,
		 * don't implement a quirk, but fallback to BIOS legacy
		 * tables instead.
		 */
		if (PN7_STA_MFID(status) != state.fid) {
			device_printf(dev, "ACPI MAX frequency not found\n");
			return (EINVAL);
		}
		sc->fsb = state.freq / 100 / pn7_fid_to_mult[state.fid];
		break;
	case PN8_TYPE:
		sc->vst = ACPI_PN8_CTRL_TO_VST(ctrl),
		sc->mvs = ACPI_PN8_CTRL_TO_MVS(ctrl),
		sc->pll = ACPI_PN8_CTRL_TO_PLL(ctrl),
		sc->rvo = ACPI_PN8_CTRL_TO_RVO(ctrl),
		sc->irt = ACPI_PN8_CTRL_TO_IRT(ctrl);
		sc->low = 0; /* XXX */

		/*
		 * powernow k8 supports only one low frequency.
		 */
		if (sc->powernow_max_states >= 2 &&
		    (sc->powernow_states[sc->powernow_max_states - 2].fid < 8))
			return (EINVAL);
		sc->fsb = state.freq / 100 / pn8_fid_to_mult[state.fid];
		break;
	}

	return (0);
}