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
typedef  int /*<<< orphan*/  u_int ;
struct fiqhandler {int /*<<< orphan*/  fh_size; int /*<<< orphan*/  fh_func; int /*<<< orphan*/ * fh_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_F ; 
 struct fiqhandler* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct fiqhandler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_list ; 
 int /*<<< orphan*/  fiq_getregs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_installhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fiq_nullhandler_code ; 
 int /*<<< orphan*/  fiq_nullhandler_size ; 
 int /*<<< orphan*/  fiq_setregs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiqhandler_stack ; 
 int /*<<< orphan*/  restore_interrupts (int /*<<< orphan*/ ) ; 

void
fiq_release(struct fiqhandler *fh)
{
	u_int oldirqstate;
	struct fiqhandler *ofh;

	oldirqstate = disable_interrupts(PSR_F);

	/*
	 * If we are the currently active FIQ handler, then we
	 * need to save our registers and pop the next one back
	 * into the vector.
	 */
	if (fh == TAILQ_FIRST(&fiqhandler_stack)) {
		if (fh->fh_regs != NULL)
			fiq_getregs(fh->fh_regs);
		TAILQ_REMOVE(&fiqhandler_stack, fh, fh_list);
		if ((ofh = TAILQ_FIRST(&fiqhandler_stack)) != NULL) {
			if (ofh->fh_regs != NULL)
				fiq_setregs(ofh->fh_regs);
			fiq_installhandler(ofh->fh_func, ofh->fh_size);
		}
	} else
		TAILQ_REMOVE(&fiqhandler_stack, fh, fh_list);

	if (TAILQ_FIRST(&fiqhandler_stack) == NULL) {
		/* Copy the NULL handler back down into the vector. */
		fiq_installhandler(fiq_nullhandler_code, fiq_nullhandler_size);

		/* Make sure FIQs are disabled when we return. */
		oldirqstate |= PSR_F;
	}

	restore_interrupts(oldirqstate);
}