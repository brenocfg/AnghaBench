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
typedef  scalar_t__ u64 ;
struct thread_struct {scalar_t__ vrsave; scalar_t__ dscr; scalar_t__ bescr; scalar_t__ ebbhr; scalar_t__ ebbrr; scalar_t__ fscr; scalar_t__ tar; scalar_t__ tidr; scalar_t__ dscr_inherit; } ;
struct TYPE_2__ {scalar_t__ dscr_default; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ALTIVEC ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_DSCR ; 
 int /*<<< orphan*/  CPU_FTR_P9_TIDR ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_DSCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int /*<<< orphan*/  SPRN_FSCR ; 
 int /*<<< orphan*/  SPRN_TAR ; 
 int /*<<< orphan*/  SPRN_TIDR ; 
 int /*<<< orphan*/  SPRN_VRSAVE ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_paca () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  thread_pkey_regs_restore (struct thread_struct*,struct thread_struct*) ; 

__attribute__((used)) static inline void restore_sprs(struct thread_struct *old_thread,
				struct thread_struct *new_thread)
{
#ifdef CONFIG_ALTIVEC
	if (cpu_has_feature(CPU_FTR_ALTIVEC) &&
	    old_thread->vrsave != new_thread->vrsave)
		mtspr(SPRN_VRSAVE, new_thread->vrsave);
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_feature(CPU_FTR_DSCR)) {
		u64 dscr = get_paca()->dscr_default;
		if (new_thread->dscr_inherit)
			dscr = new_thread->dscr;

		if (old_thread->dscr != dscr)
			mtspr(SPRN_DSCR, dscr);
	}

	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		if (old_thread->bescr != new_thread->bescr)
			mtspr(SPRN_BESCR, new_thread->bescr);
		if (old_thread->ebbhr != new_thread->ebbhr)
			mtspr(SPRN_EBBHR, new_thread->ebbhr);
		if (old_thread->ebbrr != new_thread->ebbrr)
			mtspr(SPRN_EBBRR, new_thread->ebbrr);

		if (old_thread->fscr != new_thread->fscr)
			mtspr(SPRN_FSCR, new_thread->fscr);

		if (old_thread->tar != new_thread->tar)
			mtspr(SPRN_TAR, new_thread->tar);
	}

	if (cpu_has_feature(CPU_FTR_P9_TIDR) &&
	    old_thread->tidr != new_thread->tidr)
		mtspr(SPRN_TIDR, new_thread->tidr);
#endif

	thread_pkey_regs_restore(new_thread, old_thread);
}