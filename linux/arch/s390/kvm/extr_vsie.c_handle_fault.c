#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vsie_page {int /*<<< orphan*/  fault_addr; int /*<<< orphan*/  gmap; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {scalar_t__ gmap_int_code; int gmap_write_flag; int /*<<< orphan*/  gmap_addr; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 scalar_t__ PGM_PROTECTION ; 
 TYPE_2__* current ; 
 int inject_fault (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int) ; 
 int kvm_s390_shadow_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_fault(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
{
	int rc;

	if (current->thread.gmap_int_code == PGM_PROTECTION)
		/* we can directly forward all protection exceptions */
		return inject_fault(vcpu, PGM_PROTECTION,
				    current->thread.gmap_addr, 1);

	rc = kvm_s390_shadow_fault(vcpu, vsie_page->gmap,
				   current->thread.gmap_addr);
	if (rc > 0) {
		rc = inject_fault(vcpu, rc,
				  current->thread.gmap_addr,
				  current->thread.gmap_write_flag);
		if (rc >= 0)
			vsie_page->fault_addr = current->thread.gmap_addr;
	}
	return rc;
}