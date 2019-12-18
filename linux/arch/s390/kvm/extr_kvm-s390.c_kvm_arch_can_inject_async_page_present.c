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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */

bool kvm_arch_can_inject_async_page_present(struct kvm_vcpu *vcpu)
{
	/*
	 * s390 will always inject the page directly,
	 * but we still want check_async_completion to cleanup
	 */
	return true;
}