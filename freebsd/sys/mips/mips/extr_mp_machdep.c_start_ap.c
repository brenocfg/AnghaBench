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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPCPU_SIZE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* dpcpu ; 
 scalar_t__ kmem_malloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mips_sync () ; 
 int mp_naps ; 
 scalar_t__ platform_start_ap (int) ; 

__attribute__((used)) static int
start_ap(int cpuid)
{
	int cpus, ms;

	cpus = mp_naps;
	dpcpu = (void *)kmem_malloc(DPCPU_SIZE, M_WAITOK | M_ZERO);

	mips_sync();

	if (platform_start_ap(cpuid) != 0)
		return (-1);			/* could not start AP */

	for (ms = 0; ms < 5000; ++ms) {
		if (mp_naps > cpus)
			return (0);		/* success */
		else
			DELAY(1000);
	}

	return (-2);				/* timeout initializing AP */
}