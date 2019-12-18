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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct bintime {scalar_t__ sec; int frac; } ;

/* Variables and functions */
 int /*<<< orphan*/  bintime_sub (struct bintime*,struct bintime*) ; 
 scalar_t__ bootverbose ; 
 int cpu_tick_frequency ; 
 int /*<<< orphan*/  cpu_tick_variable ; 
 int cpu_ticks () ; 
 int /*<<< orphan*/  getbinuptime (struct bintime*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
cpu_tick_calibrate(int reset)
{
	static uint64_t c_last;
	uint64_t c_this, c_delta;
	static struct bintime  t_last;
	struct bintime t_this, t_delta;
	uint32_t divi;

	if (reset) {
		/* The clock was stepped, abort & reset */
		t_last.sec = 0;
		return;
	}

	/* we don't calibrate fixed rate cputicks */
	if (!cpu_tick_variable)
		return;

	getbinuptime(&t_this);
	c_this = cpu_ticks();
	if (t_last.sec != 0) {
		c_delta = c_this - c_last;
		t_delta = t_this;
		bintime_sub(&t_delta, &t_last);
		/*
		 * Headroom:
		 * 	2^(64-20) / 16[s] =
		 * 	2^(44) / 16[s] =
		 * 	17.592.186.044.416 / 16 =
		 * 	1.099.511.627.776 [Hz]
		 */
		divi = t_delta.sec << 20;
		divi |= t_delta.frac >> (64 - 20);
		c_delta <<= 20;
		c_delta /= divi;
		if (c_delta > cpu_tick_frequency) {
			if (0 && bootverbose)
				printf("cpu_tick increased to %ju Hz\n",
				    c_delta);
			cpu_tick_frequency = c_delta;
		}
	}
	c_last = c_this;
	t_last = t_this;
}