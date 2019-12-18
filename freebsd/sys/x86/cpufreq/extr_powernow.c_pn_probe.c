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
typedef  size_t u_int ;
struct pn_softc {int fsb; int /*<<< orphan*/  vid_to_volts; int /*<<< orphan*/  pn_type; scalar_t__ errata; } ;
struct pcpu {int /*<<< orphan*/  pc_cpuid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MSR_AMDK7_FIDVID_STATUS ; 
 size_t PN7_STA_CFID (int) ; 
 size_t PN7_STA_MFID (int) ; 
 size_t PN7_STA_SFID (int) ; 
 int /*<<< orphan*/  PN7_TYPE ; 
 size_t PN8_STA_CFID (int) ; 
 size_t PN8_STA_MFID (int) ; 
 size_t PN8_STA_SFID (int) ; 
 int /*<<< orphan*/  PN8_TYPE ; 
 int /*<<< orphan*/  cpu_est_clockrate (int /*<<< orphan*/ ,int*) ; 
 struct pcpu* cpu_get_pcpu (int /*<<< orphan*/ ) ; 
 int cpu_id ; 
 struct pn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pn7_desktop_vid_to_volts ; 
 int* pn7_fid_to_mult ; 
 int /*<<< orphan*/  pn7_mobile_vid_to_volts ; 
 int* pn8_fid_to_mult ; 
 int /*<<< orphan*/  pn8_vid_to_volts ; 
 int rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pn_probe(device_t dev)
{
	struct pn_softc *sc;
	uint64_t status;
	uint64_t rate;
	struct pcpu *pc;
	u_int sfid, mfid, cfid;

	sc = device_get_softc(dev);
	sc->errata = 0;
	status = rdmsr(MSR_AMDK7_FIDVID_STATUS);

	pc = cpu_get_pcpu(dev);
	if (pc == NULL)
		return (ENODEV);

	cpu_est_clockrate(pc->pc_cpuid, &rate);

	switch (cpu_id & 0xf00) {
	case 0x600:
		sfid = PN7_STA_SFID(status);
		mfid = PN7_STA_MFID(status);
		cfid = PN7_STA_CFID(status);
		sc->pn_type = PN7_TYPE;
		sc->fsb = rate / 100000 / pn7_fid_to_mult[cfid];

		/*
		 * If start FID is different to max FID, then it is a
		 * mobile processor.  If not, it is a low powered desktop
		 * processor.
		 */
		if (PN7_STA_SFID(status) != PN7_STA_MFID(status)) {
			sc->vid_to_volts = pn7_mobile_vid_to_volts;
			device_set_desc(dev, "PowerNow! K7");
		} else {
			sc->vid_to_volts = pn7_desktop_vid_to_volts;
			device_set_desc(dev, "Cool`n'Quiet K7");
		}
		break;

	case 0xf00:
		sfid = PN8_STA_SFID(status);
		mfid = PN8_STA_MFID(status);
		cfid = PN8_STA_CFID(status);
		sc->pn_type = PN8_TYPE;
		sc->vid_to_volts = pn8_vid_to_volts;
		sc->fsb = rate / 100000 / pn8_fid_to_mult[cfid];

		if (PN8_STA_SFID(status) != PN8_STA_MFID(status))
			device_set_desc(dev, "PowerNow! K8");
		else
			device_set_desc(dev, "Cool`n'Quiet K8");
		break;
	default:
		return (ENODEV);
	}

	return (0);
}