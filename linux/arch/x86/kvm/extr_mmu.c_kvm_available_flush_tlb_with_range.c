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
struct TYPE_2__ {int tlb_remote_flush_with_range; } ;

/* Variables and functions */
 TYPE_1__* kvm_x86_ops ; 

__attribute__((used)) static inline bool kvm_available_flush_tlb_with_range(void)
{
	return kvm_x86_ops->tlb_remote_flush_with_range;
}