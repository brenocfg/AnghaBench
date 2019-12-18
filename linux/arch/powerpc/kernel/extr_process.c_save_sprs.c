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
struct thread_struct {void* tar; void* fscr; void* ebbrr; void* ebbhr; void* bescr; void* dscr; void* vrsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ALTIVEC ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_DSCR ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_DSCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int /*<<< orphan*/  SPRN_FSCR ; 
 int /*<<< orphan*/  SPRN_TAR ; 
 int /*<<< orphan*/  SPRN_VRSAVE ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_pkey_regs_save (struct thread_struct*) ; 

__attribute__((used)) static inline void save_sprs(struct thread_struct *t)
{
#ifdef CONFIG_ALTIVEC
	if (cpu_has_feature(CPU_FTR_ALTIVEC))
		t->vrsave = mfspr(SPRN_VRSAVE);
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_feature(CPU_FTR_DSCR))
		t->dscr = mfspr(SPRN_DSCR);

	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		t->bescr = mfspr(SPRN_BESCR);
		t->ebbhr = mfspr(SPRN_EBBHR);
		t->ebbrr = mfspr(SPRN_EBBRR);

		t->fscr = mfspr(SPRN_FSCR);

		/*
		 * Note that the TAR is not available for use in the kernel.
		 * (To provide this, the TAR should be backed up/restored on
		 * exception entry/exit instead, and be in pt_regs.  FIXME,
		 * this should be in pt_regs anyway (for debug).)
		 */
		t->tar = mfspr(SPRN_TAR);
	}
#endif

	thread_pkey_regs_save(t);
}