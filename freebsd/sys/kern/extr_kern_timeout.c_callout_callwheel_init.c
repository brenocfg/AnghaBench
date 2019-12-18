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
struct callout_cpu {int /*<<< orphan*/  cc_callout; } ;
struct callout {int dummy; } ;
typedef  int /*<<< orphan*/  cc_cpu ;

/* Variables and functions */
 struct callout_cpu* CC_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CALLOUT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  callout_cpu_init (struct callout_cpu*,int /*<<< orphan*/ ) ; 
 int callwheelmask ; 
 int callwheelsize ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  curcpu ; 
 int fls (int) ; 
 int imin (scalar_t__,int) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ maxfiles ; 
 scalar_t__ maxproc ; 
 int /*<<< orphan*/  memset (struct callout_cpu*,int /*<<< orphan*/ ,int) ; 
 int ncallout ; 
 int pin_default_swi ; 
 int pin_pcpu_swi ; 
 int /*<<< orphan*/  timeout_cpu ; 

__attribute__((used)) static void
callout_callwheel_init(void *dummy)
{
	struct callout_cpu *cc;

	/*
	 * Calculate the size of the callout wheel and the preallocated
	 * timeout() structures.
	 * XXX: Clip callout to result of previous function of maxusers
	 * maximum 384.  This is still huge, but acceptable.
	 */
	memset(CC_CPU(curcpu), 0, sizeof(cc_cpu));
	ncallout = imin(16 + maxproc + maxfiles, 18508);
	TUNABLE_INT_FETCH("kern.ncallout", &ncallout);

	/*
	 * Calculate callout wheel size, should be next power of two higher
	 * than 'ncallout'.
	 */
	callwheelsize = 1 << fls(ncallout);
	callwheelmask = callwheelsize - 1;

	/*
	 * Fetch whether we're pinning the swi's or not.
	 */
	TUNABLE_INT_FETCH("kern.pin_default_swi", &pin_default_swi);
	TUNABLE_INT_FETCH("kern.pin_pcpu_swi", &pin_pcpu_swi);

	/*
	 * Only BSP handles timeout(9) and receives a preallocation.
	 *
	 * XXX: Once all timeout(9) consumers are converted this can
	 * be removed.
	 */
	timeout_cpu = PCPU_GET(cpuid);
	cc = CC_CPU(timeout_cpu);
	cc->cc_callout = malloc(ncallout * sizeof(struct callout),
	    M_CALLOUT, M_WAITOK);
	callout_cpu_init(cc, timeout_cpu);
}