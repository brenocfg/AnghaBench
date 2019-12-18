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
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm_nested_guest {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_ap (unsigned long) ; 
 long get_epn (unsigned long) ; 
 int get_is (unsigned long) ; 
 int get_lpid (unsigned long) ; 
 int get_prs (unsigned int) ; 
 int get_r (unsigned int) ; 
 int get_ric (unsigned int) ; 
 int /*<<< orphan*/  kvmhv_emulate_tlbie_all_lpid (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmhv_emulate_tlbie_lpid (struct kvm_vcpu*,struct kvm_nested_guest*,int) ; 
 int kvmhv_emulate_tlbie_tlb_addr (struct kvm_vcpu*,int,int,long) ; 
 struct kvm_nested_guest* kvmhv_get_nested (struct kvm*,int,int) ; 
 int /*<<< orphan*/  kvmhv_put_nested (struct kvm_nested_guest*) ; 

__attribute__((used)) static int kvmhv_emulate_priv_tlbie(struct kvm_vcpu *vcpu, unsigned int instr,
				    unsigned long rsval, unsigned long rbval)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_nested_guest *gp;
	int r, ric, prs, is, ap;
	int lpid;
	long epn;
	int ret = 0;

	ric = get_ric(instr);
	prs = get_prs(instr);
	r = get_r(instr);
	lpid = get_lpid(rsval);
	is = get_is(rbval);

	/*
	 * These cases are invalid and are not handled:
	 * r   != 1 -> Only radix supported
	 * prs == 1 -> Not HV privileged
	 * ric == 3 -> No cluster bombs for radix
	 * is  == 1 -> Partition scoped translations not associated with pid
	 * (!is) && (ric == 1 || ric == 2) -> Not supported by ISA
	 */
	if ((!r) || (prs) || (ric == 3) || (is == 1) ||
	    ((!is) && (ric == 1 || ric == 2)))
		return -EINVAL;

	switch (is) {
	case 0:
		/*
		 * We know ric == 0
		 * Invalidate TLB for a given target address
		 */
		epn = get_epn(rbval);
		ap = get_ap(rbval);
		ret = kvmhv_emulate_tlbie_tlb_addr(vcpu, lpid, ap, epn);
		break;
	case 2:
		/* Invalidate matching LPID */
		gp = kvmhv_get_nested(kvm, lpid, false);
		if (gp) {
			kvmhv_emulate_tlbie_lpid(vcpu, gp, ric);
			kvmhv_put_nested(gp);
		}
		break;
	case 3:
		/* Invalidate ALL LPIDs */
		kvmhv_emulate_tlbie_all_lpid(vcpu, ric);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}