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
struct vsie_page {scalar_t__ fault_addr; int /*<<< orphan*/  gmap; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_s390_shadow_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void handle_last_fault(struct kvm_vcpu *vcpu,
			      struct vsie_page *vsie_page)
{
	if (vsie_page->fault_addr)
		kvm_s390_shadow_fault(vcpu, vsie_page->gmap,
				      vsie_page->fault_addr);
	vsie_page->fault_addr = 0;
}