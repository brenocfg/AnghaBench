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
typedef  int u_long ;
typedef  int u_int64_t ;
struct mem_range_softc {int mr_cap; int mr_ndesc; struct mem_range_desc* mr_desc; } ;
struct mem_range_desc {int mr_flags; int mr_base; int /*<<< orphan*/  mr_len; } ;

/* Variables and functions */
 int CR0_CD ; 
 int CR0_NW ; 
 int CR4_PGE ; 
 int MDF_ACTIVE ; 
 int MR686_FIXMTRR ; 
 int MSR_MTRR16kBase ; 
 int MSR_MTRR4kBase ; 
 int MSR_MTRR64kBase ; 
 int MSR_MTRRVarBase ; 
 int MSR_MTRRdefType ; 
 int MTRR_DEF_ENABLE ; 
 int MTRR_N16K ; 
 int MTRR_N4K ; 
 int MTRR_N64K ; 
 int MTRR_PHYSMASK_VALID ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  invltlb () ; 
 int /*<<< orphan*/  load_cr0 (int) ; 
 int /*<<< orphan*/  load_cr4 (int) ; 
 int mtrr_physmask ; 
 int rcr0 () ; 
 int rcr4 () ; 
 int rdmsr (int) ; 
 int rounddown2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  wrmsr (int,int) ; 
 int x86_mrt2mtrr (int,int) ; 

__attribute__((used)) static void
x86_mrstoreone(void *arg)
{
	struct mem_range_softc *sc = arg;
	struct mem_range_desc *mrd;
	u_int64_t omsrv, msrv;
	int i, j, msr;
	u_long cr0, cr4;

	mrd = sc->mr_desc;

	critical_enter();

	/* Disable PGE. */
	cr4 = rcr4();
	load_cr4(cr4 & ~CR4_PGE);

	/* Disable caches (CD = 1, NW = 0). */
	cr0 = rcr0();
	load_cr0((cr0 & ~CR0_NW) | CR0_CD);

	/* Flushes caches and TLBs. */
	wbinvd();
	invltlb();

	/* Disable MTRRs (E = 0). */
	wrmsr(MSR_MTRRdefType, rdmsr(MSR_MTRRdefType) & ~MTRR_DEF_ENABLE);

	/* Set fixed-range MTRRs. */
	if (sc->mr_cap & MR686_FIXMTRR) {
		msr = MSR_MTRR64kBase;
		for (i = 0; i < MTRR_N64K / 8; i++, msr++) {
			msrv = 0;
			omsrv = rdmsr(msr);
			for (j = 7; j >= 0; j--) {
				msrv = msrv << 8;
				msrv |= x86_mrt2mtrr((mrd + j)->mr_flags,
				    omsrv >> (j * 8));
			}
			wrmsr(msr, msrv);
			mrd += 8;
		}
		msr = MSR_MTRR16kBase;
		for (i = 0; i < MTRR_N16K / 8; i++, msr++) {
			msrv = 0;
			omsrv = rdmsr(msr);
			for (j = 7; j >= 0; j--) {
				msrv = msrv << 8;
				msrv |= x86_mrt2mtrr((mrd + j)->mr_flags,
				    omsrv >> (j * 8));
			}
			wrmsr(msr, msrv);
			mrd += 8;
		}
		msr = MSR_MTRR4kBase;
		for (i = 0; i < MTRR_N4K / 8; i++, msr++) {
			msrv = 0;
			omsrv = rdmsr(msr);
			for (j = 7; j >= 0; j--) {
				msrv = msrv << 8;
				msrv |= x86_mrt2mtrr((mrd + j)->mr_flags,
				    omsrv >> (j * 8));
			}
			wrmsr(msr, msrv);
			mrd += 8;
		}
	}

	/* Set remainder which must be variable MTRRs. */
	msr = MSR_MTRRVarBase;
	for (; mrd - sc->mr_desc < sc->mr_ndesc; msr += 2, mrd++) {
		/* base/type register */
		omsrv = rdmsr(msr);
		if (mrd->mr_flags & MDF_ACTIVE) {
			msrv = mrd->mr_base & mtrr_physmask;
			msrv |= x86_mrt2mtrr(mrd->mr_flags, omsrv);
		} else {
			msrv = 0;
		}
		wrmsr(msr, msrv);

		/* mask/active register */
		if (mrd->mr_flags & MDF_ACTIVE) {
			msrv = MTRR_PHYSMASK_VALID |
			    rounddown2(mtrr_physmask, mrd->mr_len);
		} else {
			msrv = 0;
		}
		wrmsr(msr + 1, msrv);
	}

	/* Flush caches and TLBs. */
	wbinvd();
	invltlb();

	/* Enable MTRRs. */
	wrmsr(MSR_MTRRdefType, rdmsr(MSR_MTRRdefType) | MTRR_DEF_ENABLE);

	/* Restore caches and PGE. */
	load_cr0(cr0);
	load_cr4(cr4);

	critical_exit();
}