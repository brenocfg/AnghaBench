#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_vcpu_book3s {TYPE_9__* dbat; TYPE_5__* ibat; int /*<<< orphan*/  sdr1; } ;
struct TYPE_13__ {int hflags; TYPE_3__* slb; int /*<<< orphan*/  pvr; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct TYPE_15__ {int /*<<< orphan*/ * dbat; int /*<<< orphan*/ * ibat; int /*<<< orphan*/ * sr; } ;
struct TYPE_11__ {TYPE_1__* slb; } ;
struct TYPE_16__ {TYPE_6__ ppc32; TYPE_2__ ppc64; int /*<<< orphan*/  sdr1; } ;
struct TYPE_17__ {TYPE_7__ s; } ;
struct kvm_sregs {TYPE_8__ u; int /*<<< orphan*/  pvr; } ;
struct TYPE_18__ {int /*<<< orphan*/  raw; } ;
struct TYPE_14__ {int /*<<< orphan*/  raw; } ;
struct TYPE_12__ {int orige; int /*<<< orphan*/  origv; } ;
struct TYPE_10__ {int slbe; int /*<<< orphan*/  slbv; } ;

/* Variables and functions */
 int BOOK3S_HFLAG_SLB ; 
 int /*<<< orphan*/  kvmppc_get_sr (struct kvm_vcpu*,int) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_arch_vcpu_ioctl_get_sregs_pr(struct kvm_vcpu *vcpu,
					    struct kvm_sregs *sregs)
{
	struct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	int i;

	sregs->pvr = vcpu->arch.pvr;

	sregs->u.s.sdr1 = to_book3s(vcpu)->sdr1;
	if (vcpu->arch.hflags & BOOK3S_HFLAG_SLB) {
		for (i = 0; i < 64; i++) {
			sregs->u.s.ppc64.slb[i].slbe = vcpu->arch.slb[i].orige | i;
			sregs->u.s.ppc64.slb[i].slbv = vcpu->arch.slb[i].origv;
		}
	} else {
		for (i = 0; i < 16; i++)
			sregs->u.s.ppc32.sr[i] = kvmppc_get_sr(vcpu, i);

		for (i = 0; i < 8; i++) {
			sregs->u.s.ppc32.ibat[i] = vcpu3s->ibat[i].raw;
			sregs->u.s.ppc32.dbat[i] = vcpu3s->dbat[i].raw;
		}
	}

	return 0;
}