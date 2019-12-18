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
typedef  unsigned long long u64 ;
struct kvm_vcpu {int dummy; } ;
struct hv_vp_assist_page {unsigned long long current_nested_vmcs; int /*<<< orphan*/  enlighten_vmentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_hv_get_assist_page (struct kvm_vcpu*,struct hv_vp_assist_page*) ; 
 scalar_t__ unlikely (int) ; 

bool nested_enlightened_vmentry(struct kvm_vcpu *vcpu, u64 *evmcs_gpa)
{
	struct hv_vp_assist_page assist_page;

	*evmcs_gpa = -1ull;

	if (unlikely(!kvm_hv_get_assist_page(vcpu, &assist_page)))
		return false;

	if (unlikely(!assist_page.enlighten_vmentry))
		return false;

	*evmcs_gpa = assist_page.current_nested_vmcs;

	return true;
}