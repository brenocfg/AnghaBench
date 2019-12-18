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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_2__ {scalar_t__ core_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ MAXCPU ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

void
platform_cpu_mask(cpuset_t *mask)
{
	uint64_t core_mask = cvmx_sysinfo_get()->core_mask;
	uint64_t i, m;

	CPU_ZERO(mask);
	for (i = 0, m = 1 ; i < MAXCPU; i++, m <<= 1)
		if (core_mask & m)
			CPU_SET(i, mask);
}