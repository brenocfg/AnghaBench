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
struct TYPE_2__ {int (* check_processor_compatibility ) () ;} ;

/* Variables and functions */
 TYPE_1__* kvm_x86_ops ; 
 int stub1 () ; 

int kvm_arch_check_processor_compat(void)
{
	return kvm_x86_ops->check_processor_compatibility();
}