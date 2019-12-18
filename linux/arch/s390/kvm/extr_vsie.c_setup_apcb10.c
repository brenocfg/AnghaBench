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
struct kvm_s390_apcb1 {int* apm; int* aqm; int* adm; } ;
struct kvm_s390_apcb0 {int* apm; int* aqm; int* adm; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ read_guest_real (struct kvm_vcpu*,unsigned long,struct kvm_s390_apcb0*,int) ; 

__attribute__((used)) static int setup_apcb10(struct kvm_vcpu *vcpu, struct kvm_s390_apcb1 *apcb_s,
			unsigned long apcb_o, struct kvm_s390_apcb1 *apcb_h)
{
	struct kvm_s390_apcb0 tmp;

	if (read_guest_real(vcpu, apcb_o, &tmp, sizeof(struct kvm_s390_apcb0)))
		return -EFAULT;

	apcb_s->apm[0] = apcb_h->apm[0] & tmp.apm[0];
	apcb_s->aqm[0] = apcb_h->aqm[0] & tmp.aqm[0] & 0xffff000000000000UL;
	apcb_s->adm[0] = apcb_h->adm[0] & tmp.adm[0] & 0xffff000000000000UL;

	return 0;

}