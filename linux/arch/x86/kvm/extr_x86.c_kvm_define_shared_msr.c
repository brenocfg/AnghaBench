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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int nr; int /*<<< orphan*/ * msrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int KVM_NR_SHARED_MSRS ; 
 TYPE_1__ shared_msrs_global ; 

void kvm_define_shared_msr(unsigned slot, u32 msr)
{
	BUG_ON(slot >= KVM_NR_SHARED_MSRS);
	shared_msrs_global.msrs[slot] = msr;
	if (slot >= shared_msrs_global.nr)
		shared_msrs_global.nr = slot + 1;
}