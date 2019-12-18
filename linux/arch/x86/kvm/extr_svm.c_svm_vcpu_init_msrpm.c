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
struct TYPE_2__ {scalar_t__ index; int /*<<< orphan*/  always; } ;

/* Variables and functions */
 int MSRPM_ALLOC_ORDER ; 
 scalar_t__ MSR_INVALID ; 
 int PAGE_SIZE ; 
 TYPE_1__* direct_access_msrs ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_msr_interception (int /*<<< orphan*/ *,scalar_t__,int,int) ; 

__attribute__((used)) static void svm_vcpu_init_msrpm(u32 *msrpm)
{
	int i;

	memset(msrpm, 0xff, PAGE_SIZE * (1 << MSRPM_ALLOC_ORDER));

	for (i = 0; direct_access_msrs[i].index != MSR_INVALID; i++) {
		if (!direct_access_msrs[i].always)
			continue;

		set_msr_interception(msrpm, direct_access_msrs[i].index, 1, 1);
	}
}