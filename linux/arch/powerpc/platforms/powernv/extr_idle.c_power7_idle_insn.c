#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct p7_sprs {void* wort; void* dscr; void* spurr; void* purr; void* fscr; void* hfscr; void* lpcr; void* rpr; void* sdr1; void* worc; void* tscr; void* uamor; void* amor; void* iamr; void* amr; } ;
struct TYPE_4__ {unsigned long thread_idle_state; unsigned long subcore_sibling_mask; void* sprg_vdso; } ;
struct TYPE_3__ {unsigned long idle_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int MSR_DR ; 
 int MSR_IR ; 
 int /*<<< orphan*/  OPAL_CONFIG_IDLE_APPLY ; 
 int /*<<< orphan*/  OPAL_CONFIG_IDLE_FASTSLEEP ; 
 int /*<<< orphan*/  OPAL_CONFIG_IDLE_UNDO ; 
 scalar_t__ OPAL_SUCCESS ; 
 unsigned long PNV_CORE_IDLE_THREAD_WINKLE_BITS ; 
 unsigned long PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT ; 
 unsigned long PNV_CORE_IDLE_WINKLE_COUNT_BITS ; 
 int PNV_CORE_IDLE_WINKLE_COUNT_SHIFT ; 
 unsigned long PNV_THREAD_NAP ; 
 unsigned long PNV_THREAD_RUNNING ; 
 unsigned long PNV_THREAD_WINKLE ; 
 int /*<<< orphan*/  SPRN_AMOR ; 
 int /*<<< orphan*/  SPRN_AMR ; 
 int /*<<< orphan*/  SPRN_DSCR ; 
 int /*<<< orphan*/  SPRN_FSCR ; 
 int /*<<< orphan*/  SPRN_HFSCR ; 
 int /*<<< orphan*/  SPRN_IAMR ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  SPRN_PURR ; 
 int /*<<< orphan*/  SPRN_RPR ; 
 int /*<<< orphan*/  SPRN_SDR1 ; 
 int /*<<< orphan*/  SPRN_SPRG3 ; 
 int /*<<< orphan*/  SPRN_SPURR ; 
 int /*<<< orphan*/  SPRN_TSCR ; 
 int /*<<< orphan*/  SPRN_UAMOR ; 
 int /*<<< orphan*/  SPRN_WORC ; 
 int /*<<< orphan*/  SPRN_WORT ; 
 unsigned long SRR1_WAKEHMI ; 
 unsigned long SRR1_WAKEMASK_P8 ; 
 unsigned long SRR1_WAKESTATE ; 
 unsigned long SRR1_WS_HVLOSS ; 
 unsigned long SRR1_WS_NOLOSS ; 
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __slb_restore_bolted_realmode () ; 
 int /*<<< orphan*/  atomic_lock_thread_idle () ; 
 int /*<<< orphan*/  atomic_unlock_and_stop_thread_idle () ; 
 int /*<<< orphan*/  atomic_unlock_thread_idle () ; 
 int cpu_first_thread_sibling (int) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 unsigned long cpu_thread_in_core (int) ; 
 int /*<<< orphan*/  hmi_exception_realmode (int /*<<< orphan*/ *) ; 
 unsigned long isa206_idle_insn_mayloss (unsigned long) ; 
 int /*<<< orphan*/  isync () ; 
 scalar_t__ likely (int) ; 
 TYPE_2__* local_paca ; 
 int mfmsr () ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,void*) ; 
 int opal_config_cpu_idle_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ opal_resync_timebase () ; 
 TYPE_1__** paca_ptrs ; 
 scalar_t__ power7_fastsleep_workaround_entry ; 
 scalar_t__ power7_fastsleep_workaround_exit ; 
 int raw_smp_processor_id () ; 
 unsigned long threads_per_core ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long power7_idle_insn(unsigned long type)
{
	int cpu = raw_smp_processor_id();
	int first = cpu_first_thread_sibling(cpu);
	unsigned long *state = &paca_ptrs[first]->idle_state;
	unsigned long thread = 1UL << cpu_thread_in_core(cpu);
	unsigned long core_thread_mask = (1UL << threads_per_core) - 1;
	unsigned long srr1;
	bool full_winkle;
	struct p7_sprs sprs = {}; /* avoid false use-uninitialised */
	bool sprs_saved = false;
	int rc;

	if (unlikely(type != PNV_THREAD_NAP)) {
		atomic_lock_thread_idle();

		BUG_ON(!(*state & thread));
		*state &= ~thread;

		if (power7_fastsleep_workaround_entry) {
			if ((*state & core_thread_mask) == 0) {
				rc = opal_config_cpu_idle_state(
						OPAL_CONFIG_IDLE_FASTSLEEP,
						OPAL_CONFIG_IDLE_APPLY);
				BUG_ON(rc);
			}
		}

		if (type == PNV_THREAD_WINKLE) {
			sprs.tscr	= mfspr(SPRN_TSCR);
			sprs.worc	= mfspr(SPRN_WORC);

			sprs.sdr1	= mfspr(SPRN_SDR1);
			sprs.rpr	= mfspr(SPRN_RPR);

			sprs.lpcr	= mfspr(SPRN_LPCR);
			if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
				sprs.hfscr	= mfspr(SPRN_HFSCR);
				sprs.fscr	= mfspr(SPRN_FSCR);
			}
			sprs.purr	= mfspr(SPRN_PURR);
			sprs.spurr	= mfspr(SPRN_SPURR);
			sprs.dscr	= mfspr(SPRN_DSCR);
			sprs.wort	= mfspr(SPRN_WORT);

			sprs_saved = true;

			/*
			 * Increment winkle counter and set all winkle bits if
			 * all threads are winkling. This allows wakeup side to
			 * distinguish between fast sleep and winkle state
			 * loss. Fast sleep still has to resync the timebase so
			 * this may not be a really big win.
			 */
			*state += 1 << PNV_CORE_IDLE_WINKLE_COUNT_SHIFT;
			if ((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS)
					>> PNV_CORE_IDLE_WINKLE_COUNT_SHIFT
					== threads_per_core)
				*state |= PNV_CORE_IDLE_THREAD_WINKLE_BITS;
			WARN_ON((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS) == 0);
		}

		atomic_unlock_thread_idle();
	}

	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		sprs.amr	= mfspr(SPRN_AMR);
		sprs.iamr	= mfspr(SPRN_IAMR);
		sprs.amor	= mfspr(SPRN_AMOR);
		sprs.uamor	= mfspr(SPRN_UAMOR);
	}

	local_paca->thread_idle_state = type;
	srr1 = isa206_idle_insn_mayloss(type);		/* go idle */
	local_paca->thread_idle_state = PNV_THREAD_RUNNING;

	WARN_ON_ONCE(!srr1);
	WARN_ON_ONCE(mfmsr() & (MSR_IR|MSR_DR));

	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		if ((srr1 & SRR1_WAKESTATE) != SRR1_WS_NOLOSS) {
			/*
			 * We don't need an isync after the mtsprs here because
			 * the upcoming mtmsrd is execution synchronizing.
			 */
			mtspr(SPRN_AMR,		sprs.amr);
			mtspr(SPRN_IAMR,	sprs.iamr);
			mtspr(SPRN_AMOR,	sprs.amor);
			mtspr(SPRN_UAMOR,	sprs.uamor);
		}
	}

	if (unlikely((srr1 & SRR1_WAKEMASK_P8) == SRR1_WAKEHMI))
		hmi_exception_realmode(NULL);

	if (likely((srr1 & SRR1_WAKESTATE) != SRR1_WS_HVLOSS)) {
		if (unlikely(type != PNV_THREAD_NAP)) {
			atomic_lock_thread_idle();
			if (type == PNV_THREAD_WINKLE) {
				WARN_ON((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS) == 0);
				*state -= 1 << PNV_CORE_IDLE_WINKLE_COUNT_SHIFT;
				*state &= ~(thread << PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT);
			}
			atomic_unlock_and_stop_thread_idle();
		}
		return srr1;
	}

	/* HV state loss */
	BUG_ON(type == PNV_THREAD_NAP);

	atomic_lock_thread_idle();

	full_winkle = false;
	if (type == PNV_THREAD_WINKLE) {
		WARN_ON((*state & PNV_CORE_IDLE_WINKLE_COUNT_BITS) == 0);
		*state -= 1 << PNV_CORE_IDLE_WINKLE_COUNT_SHIFT;
		if (*state & (thread << PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT)) {
			*state &= ~(thread << PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT);
			full_winkle = true;
			BUG_ON(!sprs_saved);
		}
	}

	WARN_ON(*state & thread);

	if ((*state & core_thread_mask) != 0)
		goto core_woken;

	/* Per-core SPRs */
	if (full_winkle) {
		mtspr(SPRN_TSCR,	sprs.tscr);
		mtspr(SPRN_WORC,	sprs.worc);
	}

	if (power7_fastsleep_workaround_exit) {
		rc = opal_config_cpu_idle_state(OPAL_CONFIG_IDLE_FASTSLEEP,
						OPAL_CONFIG_IDLE_UNDO);
		BUG_ON(rc);
	}

	/* TB */
	if (opal_resync_timebase() != OPAL_SUCCESS)
		BUG();

core_woken:
	if (!full_winkle)
		goto subcore_woken;

	if ((*state & local_paca->subcore_sibling_mask) != 0)
		goto subcore_woken;

	/* Per-subcore SPRs */
	mtspr(SPRN_SDR1,	sprs.sdr1);
	mtspr(SPRN_RPR,		sprs.rpr);

subcore_woken:
	/*
	 * isync after restoring shared SPRs and before unlocking. Unlock
	 * only contains hwsync which does not necessarily do the right
	 * thing for SPRs.
	 */
	isync();
	atomic_unlock_and_stop_thread_idle();

	/* Fast sleep does not lose SPRs */
	if (!full_winkle)
		return srr1;

	/* Per-thread SPRs */
	mtspr(SPRN_LPCR,	sprs.lpcr);
	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		mtspr(SPRN_HFSCR,	sprs.hfscr);
		mtspr(SPRN_FSCR,	sprs.fscr);
	}
	mtspr(SPRN_PURR,	sprs.purr);
	mtspr(SPRN_SPURR,	sprs.spurr);
	mtspr(SPRN_DSCR,	sprs.dscr);
	mtspr(SPRN_WORT,	sprs.wort);

	mtspr(SPRN_SPRG3,	local_paca->sprg_vdso);

	/*
	 * The SLB has to be restored here, but it sometimes still
	 * contains entries, so the __ variant must be used to prevent
	 * multi hits.
	 */
	__slb_restore_bolted_realmode();

	return srr1;
}