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
typedef  int u64 ;
struct kvm_s390_sie_block {int scaol; int itdba; int gvrd; int riccbd; int sdnxo; scalar_t__ scaoh; } ;
struct vsie_page {scalar_t__ sdnx_gpa; scalar_t__ riccbd_gpa; scalar_t__ gvrd_gpa; scalar_t__ itdba_gpa; scalar_t__ sca_gpa; struct kvm_s390_sie_block scb_s; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int hpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  unpin_guest_page (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void unpin_blocks(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
{
	struct kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	hpa_t hpa;

	hpa = (u64) scb_s->scaoh << 32 | scb_s->scaol;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->sca_gpa, hpa);
		vsie_page->sca_gpa = 0;
		scb_s->scaol = 0;
		scb_s->scaoh = 0;
	}

	hpa = scb_s->itdba;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->itdba_gpa, hpa);
		vsie_page->itdba_gpa = 0;
		scb_s->itdba = 0;
	}

	hpa = scb_s->gvrd;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->gvrd_gpa, hpa);
		vsie_page->gvrd_gpa = 0;
		scb_s->gvrd = 0;
	}

	hpa = scb_s->riccbd;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->riccbd_gpa, hpa);
		vsie_page->riccbd_gpa = 0;
		scb_s->riccbd = 0;
	}

	hpa = scb_s->sdnxo;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->sdnx_gpa, hpa);
		vsie_page->sdnx_gpa = 0;
		scb_s->sdnxo = 0;
	}
}