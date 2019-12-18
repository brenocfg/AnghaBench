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
typedef  void* u32 ;
struct kvm_s390_sie_block {unsigned long scaol; unsigned long scaoh; unsigned long itdba; int ecb; unsigned long gvrd; int eca; int ecd; unsigned long riccbd; int ecb3; unsigned long sdnxo; } ;
struct vsie_page {int sca_gpa; int itdba_gpa; int gvrd_gpa; int riccbd_gpa; int sdnx_gpa; struct kvm_s390_sie_block scb_s; struct kvm_s390_sie_block* scb_o; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct bsca_block {int dummy; } ;
typedef  unsigned long hpa_t ;
typedef  int gpa_t ;

/* Variables and functions */
 int ECA_VX ; 
 int ECB3_RI ; 
 int ECB_GS ; 
 int ECB_TE ; 
 int ECD_ETOKENF ; 
 int ECD_HOSTREGMGMT ; 
 int /*<<< orphan*/  KVM_S390_VM_CPU_FEAT_64BSCAO ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int READ_ONCE (unsigned long) ; 
 int kvm_s390_get_prefix (struct kvm_vcpu*) ; 
 int pin_guest_page (int /*<<< orphan*/ ,int,unsigned long*) ; 
 int set_validity_icpt (struct kvm_s390_sie_block*,int) ; 
 scalar_t__ test_kvm_cpu_feat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpin_blocks (struct kvm_vcpu*,struct vsie_page*) ; 

__attribute__((used)) static int pin_blocks(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
{
	struct kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	struct kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	hpa_t hpa;
	gpa_t gpa;
	int rc = 0;

	gpa = READ_ONCE(scb_o->scaol) & ~0xfUL;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_64BSCAO))
		gpa |= (u64) READ_ONCE(scb_o->scaoh) << 32;
	if (gpa) {
		if (gpa < 2 * PAGE_SIZE)
			rc = set_validity_icpt(scb_s, 0x0038U);
		else if ((gpa & ~0x1fffUL) == kvm_s390_get_prefix(vcpu))
			rc = set_validity_icpt(scb_s, 0x0011U);
		else if ((gpa & PAGE_MASK) !=
			 ((gpa + sizeof(struct bsca_block) - 1) & PAGE_MASK))
			rc = set_validity_icpt(scb_s, 0x003bU);
		if (!rc) {
			rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
			if (rc)
				rc = set_validity_icpt(scb_s, 0x0034U);
		}
		if (rc)
			goto unpin;
		vsie_page->sca_gpa = gpa;
		scb_s->scaoh = (u32)((u64)hpa >> 32);
		scb_s->scaol = (u32)(u64)hpa;
	}

	gpa = READ_ONCE(scb_o->itdba) & ~0xffUL;
	if (gpa && (scb_s->ecb & ECB_TE)) {
		if (gpa < 2 * PAGE_SIZE) {
			rc = set_validity_icpt(scb_s, 0x0080U);
			goto unpin;
		}
		/* 256 bytes cannot cross page boundaries */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (rc) {
			rc = set_validity_icpt(scb_s, 0x0080U);
			goto unpin;
		}
		vsie_page->itdba_gpa = gpa;
		scb_s->itdba = hpa;
	}

	gpa = READ_ONCE(scb_o->gvrd) & ~0x1ffUL;
	if (gpa && (scb_s->eca & ECA_VX) && !(scb_s->ecd & ECD_HOSTREGMGMT)) {
		if (gpa < 2 * PAGE_SIZE) {
			rc = set_validity_icpt(scb_s, 0x1310U);
			goto unpin;
		}
		/*
		 * 512 bytes vector registers cannot cross page boundaries
		 * if this block gets bigger, we have to shadow it.
		 */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (rc) {
			rc = set_validity_icpt(scb_s, 0x1310U);
			goto unpin;
		}
		vsie_page->gvrd_gpa = gpa;
		scb_s->gvrd = hpa;
	}

	gpa = READ_ONCE(scb_o->riccbd) & ~0x3fUL;
	if (gpa && (scb_s->ecb3 & ECB3_RI)) {
		if (gpa < 2 * PAGE_SIZE) {
			rc = set_validity_icpt(scb_s, 0x0043U);
			goto unpin;
		}
		/* 64 bytes cannot cross page boundaries */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (rc) {
			rc = set_validity_icpt(scb_s, 0x0043U);
			goto unpin;
		}
		/* Validity 0x0044 will be checked by SIE */
		vsie_page->riccbd_gpa = gpa;
		scb_s->riccbd = hpa;
	}
	if (((scb_s->ecb & ECB_GS) && !(scb_s->ecd & ECD_HOSTREGMGMT)) ||
	    (scb_s->ecd & ECD_ETOKENF)) {
		unsigned long sdnxc;

		gpa = READ_ONCE(scb_o->sdnxo) & ~0xfUL;
		sdnxc = READ_ONCE(scb_o->sdnxo) & 0xfUL;
		if (!gpa || gpa < 2 * PAGE_SIZE) {
			rc = set_validity_icpt(scb_s, 0x10b0U);
			goto unpin;
		}
		if (sdnxc < 6 || sdnxc > 12) {
			rc = set_validity_icpt(scb_s, 0x10b1U);
			goto unpin;
		}
		if (gpa & ((1 << sdnxc) - 1)) {
			rc = set_validity_icpt(scb_s, 0x10b2U);
			goto unpin;
		}
		/* Due to alignment rules (checked above) this cannot
		 * cross page boundaries
		 */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (rc) {
			rc = set_validity_icpt(scb_s, 0x10b0U);
			goto unpin;
		}
		vsie_page->sdnx_gpa = gpa;
		scb_s->sdnxo = hpa | sdnxc;
	}
	return 0;
unpin:
	unpin_blocks(vcpu, vsie_page);
	return rc;
}