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
typedef  int u32 ;
struct thread_info {unsigned int cpu; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int FPEXC_EN ; 
 int NOTIFY_DONE ; 
#define  THREAD_NOTIFY_COPY 131 
#define  THREAD_NOTIFY_EXIT 130 
#define  THREAD_NOTIFY_FLUSH 129 
#define  THREAD_NOTIFY_SWITCH 128 
 int fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vfp_current_hw_state ; 
 int /*<<< orphan*/  vfp_save_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfp_thread_copy (struct thread_info*) ; 
 int /*<<< orphan*/  vfp_thread_exit (struct thread_info*) ; 
 int /*<<< orphan*/  vfp_thread_flush (struct thread_info*) ; 

__attribute__((used)) static int vfp_notifier(struct notifier_block *self, unsigned long cmd, void *v)
{
	struct thread_info *thread = v;
	u32 fpexc;
#ifdef CONFIG_SMP
	unsigned int cpu;
#endif

	switch (cmd) {
	case THREAD_NOTIFY_SWITCH:
		fpexc = fmrx(FPEXC);

#ifdef CONFIG_SMP
		cpu = thread->cpu;

		/*
		 * On SMP, if VFP is enabled, save the old state in
		 * case the thread migrates to a different CPU. The
		 * restoring is done lazily.
		 */
		if ((fpexc & FPEXC_EN) && vfp_current_hw_state[cpu])
			vfp_save_state(vfp_current_hw_state[cpu], fpexc);
#endif

		/*
		 * Always disable VFP so we can lazily save/restore the
		 * old state.
		 */
		fmxr(FPEXC, fpexc & ~FPEXC_EN);
		break;

	case THREAD_NOTIFY_FLUSH:
		vfp_thread_flush(thread);
		break;

	case THREAD_NOTIFY_EXIT:
		vfp_thread_exit(thread);
		break;

	case THREAD_NOTIFY_COPY:
		vfp_thread_copy(thread);
		break;
	}

	return NOTIFY_DONE;
}