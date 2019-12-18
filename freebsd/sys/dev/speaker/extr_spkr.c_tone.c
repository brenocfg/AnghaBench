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

/* Variables and functions */
 int PCATCH ; 
 int SPKRPRI ; 
 int /*<<< orphan*/  disable_intr () ; 
 int /*<<< orphan*/  enable_intr () ; 
 int /*<<< orphan*/  endtone ; 
 unsigned int hz ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int) ; 
 int splclock () ; 
 int /*<<< orphan*/  splx (int) ; 
 scalar_t__ timer_spkr_acquire () ; 
 int /*<<< orphan*/  timer_spkr_release () ; 
 int /*<<< orphan*/  timer_spkr_setfreq (unsigned int) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static void
tone(unsigned int thz, unsigned int centisecs)
{
	int sps, timo;

	if (thz <= 0)
		return;

#ifdef DEBUG
	(void) printf("tone: thz=%d centisecs=%d\n", thz, centisecs);
#endif /* DEBUG */

	/* set timer to generate clicks at given frequency in Hertz */
	sps = splclock();

	if (timer_spkr_acquire()) {
		/* enter list of waiting procs ??? */
		splx(sps);
		return;
	}
	splx(sps);
	disable_intr();
	timer_spkr_setfreq(thz);
	enable_intr();

	/*
	 * Set timeout to endtone function, then give up the timeslice.
	 * This is so other processes can execute while the tone is being
	 * emitted.
	 */
	timo = centisecs * hz / 100;
	if (timo > 0)
		tsleep(&endtone, SPKRPRI | PCATCH, "spkrtn", timo);
	sps = splclock();
	timer_spkr_release();
	splx(sps);
}