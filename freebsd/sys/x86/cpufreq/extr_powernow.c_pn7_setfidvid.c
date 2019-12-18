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
struct pn_softc {int errata; int /*<<< orphan*/  sgtc; } ;

/* Variables and functions */
 int A0_ERRATA ; 
 int /*<<< orphan*/  MSR_AMDK7_FIDVID_CTL ; 
 int /*<<< orphan*/  MSR_AMDK7_FIDVID_STATUS ; 
 int PN7_CTR_FID (int) ; 
 int PN7_CTR_FIDC ; 
 int PN7_CTR_FIDCHRATIO ; 
 int PN7_CTR_SGTC (int /*<<< orphan*/ ) ; 
 int PN7_CTR_VID (int) ; 
 int PN7_CTR_VIDC ; 
 int PN7_STA_CFID (int) ; 
 int PN7_STA_CVID (int) ; 
 int /*<<< orphan*/  disable_intr () ; 
 int /*<<< orphan*/  enable_intr () ; 
 scalar_t__* pn7_fid_to_mult ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pn7_setfidvid(struct pn_softc *sc, int fid, int vid)
{
	int cfid, cvid;
	uint64_t status, ctl;

	status = rdmsr(MSR_AMDK7_FIDVID_STATUS);
	cfid = PN7_STA_CFID(status);
	cvid = PN7_STA_CVID(status);

	/* We're already at the requested level. */
	if (fid == cfid && vid == cvid)
		return (0);

	ctl = rdmsr(MSR_AMDK7_FIDVID_CTL) & PN7_CTR_FIDCHRATIO;

	ctl |= PN7_CTR_FID(fid);
	ctl |= PN7_CTR_VID(vid);
	ctl |= PN7_CTR_SGTC(sc->sgtc);

	if (sc->errata & A0_ERRATA)
		disable_intr();

	if (pn7_fid_to_mult[fid] < pn7_fid_to_mult[cfid]) {
		wrmsr(MSR_AMDK7_FIDVID_CTL, ctl | PN7_CTR_FIDC);
		if (vid != cvid)
			wrmsr(MSR_AMDK7_FIDVID_CTL, ctl | PN7_CTR_VIDC);
	} else {
		wrmsr(MSR_AMDK7_FIDVID_CTL, ctl | PN7_CTR_VIDC);
		if (fid != cfid)
			wrmsr(MSR_AMDK7_FIDVID_CTL, ctl | PN7_CTR_FIDC);
	}

	if (sc->errata & A0_ERRATA)
		enable_intr();

	return (0);
}