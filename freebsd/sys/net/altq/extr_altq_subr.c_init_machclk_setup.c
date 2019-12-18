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
 int CPUID_TSC ; 
 scalar_t__ atomic_load_acq_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cpu_feature ; 
 int machclk_usepcc ; 
 int /*<<< orphan*/  tbr_callout ; 
 int /*<<< orphan*/  tsc_freq ; 

__attribute__((used)) static void
init_machclk_setup(void)
{
#if (__FreeBSD_version >= 600000)
	callout_init(&tbr_callout, 0);
#endif

	machclk_usepcc = 1;

#if (!defined(__amd64__) && !defined(__i386__)) || defined(ALTQ_NOPCC)
	machclk_usepcc = 0;
#endif
#if defined(__FreeBSD__) && defined(SMP)
	machclk_usepcc = 0;
#endif
#if defined(__NetBSD__) && defined(MULTIPROCESSOR)
	machclk_usepcc = 0;
#endif
#if defined(__amd64__) || defined(__i386__)
	/* check if TSC is available */
	if ((cpu_feature & CPUID_TSC) == 0 ||
	    atomic_load_acq_64(&tsc_freq) == 0)
		machclk_usepcc = 0;
#endif
}