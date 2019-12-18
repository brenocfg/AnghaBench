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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ u_long ;
typedef  int u_int ;
struct pst_header {int cpuid; int maxfid; int startvid; int numpstates; int fsb; } ;
struct psb_header {int version; int settlingtime; int /*<<< orphan*/  res1; } ;
struct pn_softc {int pn_type; int vst; int sgtc; int fsb; int powernow_max_states; int /*<<< orphan*/  low; int /*<<< orphan*/  mvs; int /*<<< orphan*/  irt; int /*<<< orphan*/  rvo; int /*<<< orphan*/  errata; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  A0_ERRATA ; 
 scalar_t__ BIOS_PADDRTOVADDR (scalar_t__) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MSR_AMDK7_FIDVID_STATUS ; 
 int PN7_STA_MFID (int) ; 
 int PN7_STA_SVID (int) ; 
#define  PN7_TYPE 129 
 int /*<<< orphan*/  PN8_PSB_TO_BATT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PN8_PSB_TO_IRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PN8_PSB_TO_MVS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PN8_PSB_TO_RVO (int /*<<< orphan*/ ) ; 
 int PN8_STA_MFID (int) ; 
 int PN8_STA_MVID (int) ; 
#define  PN8_TYPE 128 
 int /*<<< orphan*/  PSB_LEN ; 
 int /*<<< orphan*/  PSB_OFF ; 
 int /*<<< orphan*/  PSB_SIG ; 
 int /*<<< orphan*/  PSB_START ; 
 int /*<<< orphan*/  PSB_STEP ; 
 int abs (int) ; 
 scalar_t__ bios_sigsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ cpuid_is_k7 (int) ; 
 int decode_pst (struct pn_softc*,int /*<<< orphan*/ *,int) ; 
 struct pn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pn_decode_pst(device_t dev)
{
	int maxpst;
	struct pn_softc *sc;
	u_int cpuid, maxfid, startvid;
	u_long sig;
	struct psb_header *psb;
	uint8_t *p;
	u_int regs[4];
	uint64_t status;

	sc = device_get_softc(dev);

	do_cpuid(0x80000001, regs);
	cpuid = regs[0];

	if ((cpuid & 0xfff) == 0x760)
		sc->errata |= A0_ERRATA;

	status = rdmsr(MSR_AMDK7_FIDVID_STATUS);

	switch (sc->pn_type) {
	case PN7_TYPE:
		maxfid = PN7_STA_MFID(status);
		startvid = PN7_STA_SVID(status);
		break;
	case PN8_TYPE:
		maxfid = PN8_STA_MFID(status);
		/*
		 * we should actually use a variable named 'maxvid' if K8,
		 * but why introducing a new variable for that?
		 */
		startvid = PN8_STA_MVID(status);
		break;
	default:
		return (ENODEV);
	}

	if (bootverbose) {
		device_printf(dev, "STATUS: 0x%jx\n", status);
		device_printf(dev, "STATUS: maxfid: 0x%02x\n", maxfid);
		device_printf(dev, "STATUS: %s: 0x%02x\n",
		    sc->pn_type == PN7_TYPE ? "startvid" : "maxvid",
		    startvid);
	}

	sig = bios_sigsearch(PSB_START, PSB_SIG, PSB_LEN, PSB_STEP, PSB_OFF);
	if (sig) {
		struct pst_header *pst;

		psb = (struct psb_header*)(uintptr_t)BIOS_PADDRTOVADDR(sig);

		switch (psb->version) {
		default:
			return (ENODEV);
		case 0x14:
			/*
			 * We can't be picky about numpst since at least
			 * some systems have a value of 1 and some have 2.
			 * We trust that cpuid_is_k7() will be better at
			 * catching that we're on a K8 anyway.
			 */
			if (sc->pn_type != PN8_TYPE)
				return (EINVAL);
			sc->vst = psb->settlingtime;
			sc->rvo = PN8_PSB_TO_RVO(psb->res1);
			sc->irt = PN8_PSB_TO_IRT(psb->res1);
			sc->mvs = PN8_PSB_TO_MVS(psb->res1);
			sc->low = PN8_PSB_TO_BATT(psb->res1);
			if (bootverbose) {
				device_printf(dev, "PSB: VST: %d\n",
				    psb->settlingtime);
				device_printf(dev, "PSB: RVO %x IRT %d "
				    "MVS %d BATT %d\n",
				    sc->rvo,
				    sc->irt,
				    sc->mvs,
				    sc->low);
			}
			break;
		case 0x12:
			if (sc->pn_type != PN7_TYPE)
				return (EINVAL);
			sc->sgtc = psb->settlingtime * sc->fsb;
			if (sc->sgtc < 100 * sc->fsb)
				sc->sgtc = 100 * sc->fsb;
			break;
		}

		p = ((uint8_t *) psb) + sizeof(struct psb_header);
		pst = (struct pst_header*) p;

		maxpst = 200;

		do {
			struct pst_header *pst = (struct pst_header*) p;

			if (cpuid == pst->cpuid &&
			    maxfid == pst->maxfid &&
			    startvid == pst->startvid) {
				sc->powernow_max_states = pst->numpstates;
				switch (sc->pn_type) {
				case PN7_TYPE:
					if (abs(sc->fsb - pst->fsb) > 5)
						continue;
					break;
				case PN8_TYPE:
					break;
				}
				return (decode_pst(sc,
				    p + sizeof(struct pst_header),
				    sc->powernow_max_states));
			}

			p += sizeof(struct pst_header) + (2 * pst->numpstates);
		} while (cpuid_is_k7(pst->cpuid) && maxpst--);

		device_printf(dev, "no match for extended cpuid %.3x\n", cpuid);
	}

	return (ENODEV);
}