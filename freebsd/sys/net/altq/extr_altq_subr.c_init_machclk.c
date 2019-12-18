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
typedef  int u_int64_t ;
typedef  int u_int ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int MACHCLK_SHIFT ; 
 int PCATCH ; 
 int PWAIT ; 
 int atomic_load_acq_64 (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  init_machclk_setup () ; 
 int machclk_freq ; 
 int machclk_per_tick ; 
 scalar_t__ machclk_usepcc ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int read_machclk () ; 
 int /*<<< orphan*/  tsc_freq ; 
 int /*<<< orphan*/  tsleep (int*,int,char*,int) ; 

void
init_machclk(void)
{
	static int called;

	/* Call one-time initialization function. */
	if (!called) {
		init_machclk_setup();
		called = 1;
	}

	if (machclk_usepcc == 0) {
		/* emulate 256MHz using microtime() */
		machclk_freq = 1000000 << MACHCLK_SHIFT;
		machclk_per_tick = machclk_freq / hz;
#ifdef ALTQ_DEBUG
		printf("altq: emulate %uHz cpu clock\n", machclk_freq);
#endif
		return;
	}

	/*
	 * if the clock frequency (of Pentium TSC or Alpha PCC) is
	 * accessible, just use it.
	 */
#if defined(__amd64__) || defined(__i386__)
	machclk_freq = atomic_load_acq_64(&tsc_freq);
#endif

	/*
	 * if we don't know the clock frequency, measure it.
	 */
	if (machclk_freq == 0) {
		static int	wait;
		struct timeval	tv_start, tv_end;
		u_int64_t	start, end, diff;
		int		timo;

		microtime(&tv_start);
		start = read_machclk();
		timo = hz;	/* 1 sec */
		(void)tsleep(&wait, PWAIT | PCATCH, "init_machclk", timo);
		microtime(&tv_end);
		end = read_machclk();
		diff = (u_int64_t)(tv_end.tv_sec - tv_start.tv_sec) * 1000000
		    + tv_end.tv_usec - tv_start.tv_usec;
		if (diff != 0)
			machclk_freq = (u_int)((end - start) * 1000000 / diff);
	}

	machclk_per_tick = machclk_freq / hz;

#ifdef ALTQ_DEBUG
	printf("altq: CPU clock: %uHz\n", machclk_freq);
#endif
}