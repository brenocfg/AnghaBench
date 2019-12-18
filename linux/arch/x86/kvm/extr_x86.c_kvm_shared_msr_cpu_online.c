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
struct TYPE_2__ {unsigned int nr; int /*<<< orphan*/ * msrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  shared_msr_update (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__ shared_msrs_global ; 

__attribute__((used)) static void kvm_shared_msr_cpu_online(void)
{
	unsigned i;

	for (i = 0; i < shared_msrs_global.nr; ++i)
		shared_msr_update(i, shared_msrs_global.msrs[i]);
}