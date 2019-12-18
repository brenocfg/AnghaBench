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
struct vsie_page {struct kvm_s390_sie_block* scb_o; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_s390_sie_block {int dummy; } ;
typedef  scalar_t__ hpa_t ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  PGM_ADDRESSING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int pin_guest_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int pin_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page,
		   gpa_t gpa)
{
	hpa_t hpa;
	int rc;

	rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
	if (rc) {
		rc = kvm_s390_inject_program_int(vcpu, PGM_ADDRESSING);
		WARN_ON_ONCE(rc);
		return 1;
	}
	vsie_page->scb_o = (struct kvm_s390_sie_block *) hpa;
	return 0;
}