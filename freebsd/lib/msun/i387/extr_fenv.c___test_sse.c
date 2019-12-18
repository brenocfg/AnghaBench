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
 int /*<<< orphan*/  __SSE_NO ; 
 int /*<<< orphan*/  __SSE_YES ; 
 int /*<<< orphan*/  __has_sse ; 
 int /*<<< orphan*/  cpuid_dx (int*) ; 
 int /*<<< orphan*/  getfl (int*) ; 
 int /*<<< orphan*/  setfl (int) ; 

int
__test_sse(void)
{
	int flag, nflag;
	int dx_features;

	/* Am I a 486? */
	getfl(&flag);
	nflag = flag ^ 0x200000;
	setfl(nflag);
	getfl(&nflag);
	if (flag != nflag) {
		/* Not a 486, so CPUID should work. */
		cpuid_dx(&dx_features);
		if (dx_features & 0x2000000) {
			__has_sse = __SSE_YES;
			return (1);
		}
	}
	__has_sse = __SSE_NO;
	return (0);
}