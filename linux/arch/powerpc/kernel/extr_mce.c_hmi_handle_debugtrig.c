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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {long hmi_p9_special_emu; } ;

/* Variables and functions */
 int DTRIG_UNKNOWN ; 
#define  DTRIG_VECTOR_CI 128 
 unsigned long HMER_DEBUG_TRIG ; 
 int /*<<< orphan*/  SPRN_HMEER ; 
 int /*<<< orphan*/  SPRN_HMER ; 
 int hmer_debug_trig_function ; 
 TYPE_1__* local_paca ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

long hmi_handle_debugtrig(struct pt_regs *regs)
{
	unsigned long hmer = mfspr(SPRN_HMER);
	long ret = 0;

	/* HMER_DEBUG_TRIG bit is used for various workarounds on P9 */
	if (!((hmer & HMER_DEBUG_TRIG)
	      && hmer_debug_trig_function != DTRIG_UNKNOWN))
		return -1;
		
	hmer &= ~HMER_DEBUG_TRIG;
	/* HMER is a write-AND register */
	mtspr(SPRN_HMER, ~HMER_DEBUG_TRIG);

	switch (hmer_debug_trig_function) {
	case DTRIG_VECTOR_CI:
		/*
		 * Now to avoid problems with soft-disable we
		 * only do the emulation if we are coming from
		 * host user space
		 */
		if (regs && user_mode(regs))
			ret = local_paca->hmi_p9_special_emu = 1;

		break;

	default:
		break;
	}

	/*
	 * See if any other HMI causes remain to be handled
	 */
	if (hmer & mfspr(SPRN_HMEER))
		return -1;

	return ret;
}