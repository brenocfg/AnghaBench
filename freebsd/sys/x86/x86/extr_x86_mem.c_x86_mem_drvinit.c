#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * mr_op; } ;

/* Variables and functions */
 int CPUID_MTRR ; 
 int cpu_feature ; 
 TYPE_1__ mem_range_softc ; 
 scalar_t__ mtrrs_disabled ; 
 int /*<<< orphan*/  x86_mrinit (TYPE_1__*) ; 
 int /*<<< orphan*/  x86_mrops ; 

__attribute__((used)) static void
x86_mem_drvinit(void *unused)
{

	if (mtrrs_disabled)
		return;
	if (!(cpu_feature & CPUID_MTRR))
		return;
	mem_range_softc.mr_op = &x86_mrops;
	x86_mrinit(&mem_range_softc);
}