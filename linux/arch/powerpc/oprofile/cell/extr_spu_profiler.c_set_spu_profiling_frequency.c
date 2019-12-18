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
 unsigned int SCALE_SHIFT ; 
 unsigned int USEC_PER_SEC ; 
 int ppc_proc_freq ; 
 unsigned long profiling_interval ; 

void set_spu_profiling_frequency(unsigned int freq_khz, unsigned int cycles_reset)
{
	unsigned long ns_per_cyc;

	if (!freq_khz)
		freq_khz = ppc_proc_freq/1000;

	/* To calculate a timeout in nanoseconds, the basic
	 * formula is ns = cycles_reset * (NSEC_PER_SEC / cpu frequency).
	 * To avoid floating point math, we use the scale math
	 * technique as described in linux/jiffies.h.  We use
	 * a scale factor of SCALE_SHIFT, which provides 4 decimal places
	 * of precision.  This is close enough for the purpose at hand.
	 *
	 * The value of the timeout should be small enough that the hw
	 * trace buffer will not get more than about 1/3 full for the
	 * maximum user specified (the LFSR value) hw sampling frequency.
	 * This is to ensure the trace buffer will never fill even if the
	 * kernel thread scheduling varies under a heavy system load.
	 */

	ns_per_cyc = (USEC_PER_SEC << SCALE_SHIFT)/freq_khz;
	profiling_interval = (ns_per_cyc * cycles_reset) >> SCALE_SHIFT;

}