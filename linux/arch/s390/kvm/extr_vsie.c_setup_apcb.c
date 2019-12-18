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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_s390_crypto_cb {int /*<<< orphan*/  apcb0; int /*<<< orphan*/  apcb1; } ;

/* Variables and functions */
#define  CRYCB_FORMAT0 130 
#define  CRYCB_FORMAT1 129 
#define  CRYCB_FORMAT2 128 
 int EACCES ; 
 int EINVAL ; 
 int const PAGE_MASK ; 
 int setup_apcb00 (struct kvm_vcpu*,unsigned long*,unsigned long,unsigned long*) ; 
 int setup_apcb10 (struct kvm_vcpu*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int setup_apcb11 (struct kvm_vcpu*,unsigned long*,unsigned long,unsigned long*) ; 

__attribute__((used)) static int setup_apcb(struct kvm_vcpu *vcpu, struct kvm_s390_crypto_cb *crycb_s,
	       const u32 crycb_o,
	       struct kvm_s390_crypto_cb *crycb_h,
	       int fmt_o, int fmt_h)
{
	struct kvm_s390_crypto_cb *crycb;

	crycb = (struct kvm_s390_crypto_cb *) (unsigned long)crycb_o;

	switch (fmt_o) {
	case CRYCB_FORMAT2:
		if ((crycb_o & PAGE_MASK) != ((crycb_o + 256) & PAGE_MASK))
			return -EACCES;
		if (fmt_h != CRYCB_FORMAT2)
			return -EINVAL;
		return setup_apcb11(vcpu, (unsigned long *)&crycb_s->apcb1,
				    (unsigned long) &crycb->apcb1,
				    (unsigned long *)&crycb_h->apcb1);
	case CRYCB_FORMAT1:
		switch (fmt_h) {
		case CRYCB_FORMAT2:
			return setup_apcb10(vcpu, &crycb_s->apcb1,
					    (unsigned long) &crycb->apcb0,
					    &crycb_h->apcb1);
		case CRYCB_FORMAT1:
			return setup_apcb00(vcpu,
					    (unsigned long *) &crycb_s->apcb0,
					    (unsigned long) &crycb->apcb0,
					    (unsigned long *) &crycb_h->apcb0);
		}
		break;
	case CRYCB_FORMAT0:
		if ((crycb_o & PAGE_MASK) != ((crycb_o + 32) & PAGE_MASK))
			return -EACCES;

		switch (fmt_h) {
		case CRYCB_FORMAT2:
			return setup_apcb10(vcpu, &crycb_s->apcb1,
					    (unsigned long) &crycb->apcb0,
					    &crycb_h->apcb1);
		case CRYCB_FORMAT1:
		case CRYCB_FORMAT0:
			return setup_apcb00(vcpu,
					    (unsigned long *) &crycb_s->apcb0,
					    (unsigned long) &crycb->apcb0,
					    (unsigned long *) &crycb_h->apcb0);
		}
	}
	return -EINVAL;
}