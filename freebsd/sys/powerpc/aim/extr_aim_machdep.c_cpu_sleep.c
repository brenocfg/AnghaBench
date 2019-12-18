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
typedef  int /*<<< orphan*/  u_quad_t ;
struct thread {struct thread* td_pcb; } ;
typedef  int register_t ;
typedef  struct thread jmp_buf ;

/* Variables and functions */
 int HID0_DOZE ; 
 int HID0_NAP ; 
 int HID0_SLEEP ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (struct thread*,struct thread*) ; 
 int PSL_POW ; 
 int /*<<< orphan*/  SPR_HID0 ; 
 int /*<<< orphan*/  SPR_SPRG0 ; 
 int /*<<< orphan*/  SPR_SPRG1 ; 
 int /*<<< orphan*/  SPR_SPRG2 ; 
 int /*<<< orphan*/  SPR_SPRG3 ; 
 int /*<<< orphan*/  SPR_SRR0 ; 
 int /*<<< orphan*/  SPR_SRR1 ; 
 int /*<<< orphan*/  ap_pcpu ; 
 struct thread* curpcb ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  enable_fpu (struct thread*) ; 
 int /*<<< orphan*/  enable_vec (struct thread*) ; 
 int /*<<< orphan*/  flush_disable_caches () ; 
 int /*<<< orphan*/  fputhread ; 
 int /*<<< orphan*/  isync () ; 
 int mfmsr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mftb () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcpup ; 
 int /*<<< orphan*/  platform_smp_timebase_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_activate (struct thread*) ; 
 int /*<<< orphan*/  powerpc_sync () ; 
 struct thread* restore ; 
 int /*<<< orphan*/  save_fpu (struct thread*) ; 
 int /*<<< orphan*/  save_vec (struct thread*) ; 
 scalar_t__ setjmp (struct thread) ; 
 int /*<<< orphan*/  vecthread ; 

void
cpu_sleep()
{
	static u_quad_t timebase = 0;
	static register_t sprgs[4];
	static register_t srrs[2];

	jmp_buf resetjb;
	struct thread *fputd;
	struct thread *vectd;
	register_t hid0;
	register_t msr;
	register_t saved_msr;

	ap_pcpu = pcpup;

	PCPU_SET(restore, &resetjb);

	saved_msr = mfmsr();
	fputd = PCPU_GET(fputhread);
	vectd = PCPU_GET(vecthread);
	if (fputd != NULL)
		save_fpu(fputd);
	if (vectd != NULL)
		save_vec(vectd);
	if (setjmp(resetjb) == 0) {
		sprgs[0] = mfspr(SPR_SPRG0);
		sprgs[1] = mfspr(SPR_SPRG1);
		sprgs[2] = mfspr(SPR_SPRG2);
		sprgs[3] = mfspr(SPR_SPRG3);
		srrs[0] = mfspr(SPR_SRR0);
		srrs[1] = mfspr(SPR_SRR1);
		timebase = mftb();
		powerpc_sync();
		flush_disable_caches();
		hid0 = mfspr(SPR_HID0);
		hid0 = (hid0 & ~(HID0_DOZE | HID0_NAP)) | HID0_SLEEP;
		powerpc_sync();
		isync();
		msr = mfmsr() | PSL_POW;
		mtspr(SPR_HID0, hid0);
		powerpc_sync();

		while (1)
			mtmsr(msr);
	}
	platform_smp_timebase_sync(timebase, 0);
	PCPU_SET(curthread, curthread);
	PCPU_SET(curpcb, curthread->td_pcb);
	pmap_activate(curthread);
	powerpc_sync();
	mtspr(SPR_SPRG0, sprgs[0]);
	mtspr(SPR_SPRG1, sprgs[1]);
	mtspr(SPR_SPRG2, sprgs[2]);
	mtspr(SPR_SPRG3, sprgs[3]);
	mtspr(SPR_SRR0, srrs[0]);
	mtspr(SPR_SRR1, srrs[1]);
	mtmsr(saved_msr);
	if (fputd == curthread)
		enable_fpu(curthread);
	if (vectd == curthread)
		enable_vec(curthread);
	powerpc_sync();
}