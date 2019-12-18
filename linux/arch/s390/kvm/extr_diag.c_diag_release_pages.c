#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  gmap; TYPE_4__* sie_block; } ;
struct TYPE_11__ {int /*<<< orphan*/  diagnose_10; } ;
struct kvm_vcpu {TYPE_6__ arch; TYPE_5__ stat; TYPE_3__* run; } ;
struct TYPE_10__ {int ipa; } ;
struct TYPE_7__ {unsigned long* gprs; } ;
struct TYPE_8__ {TYPE_1__ regs; } ;
struct TYPE_9__ {TYPE_2__ s; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PGM_SPECIFICATION ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gmap_discard (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long kvm_s390_get_prefix (struct kvm_vcpu*) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diag_release_pages(struct kvm_vcpu *vcpu)
{
	unsigned long start, end;
	unsigned long prefix  = kvm_s390_get_prefix(vcpu);

	start = vcpu->run->s.regs.gprs[(vcpu->arch.sie_block->ipa & 0xf0) >> 4];
	end = vcpu->run->s.regs.gprs[vcpu->arch.sie_block->ipa & 0xf] + PAGE_SIZE;
	vcpu->stat.diagnose_10++;

	if (start & ~PAGE_MASK || end & ~PAGE_MASK || start >= end
	    || start < 2 * PAGE_SIZE)
		return kvm_s390_inject_program_int(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 5, "diag release pages %lX %lX", start, end);

	/*
	 * We checked for start >= end above, so lets check for the
	 * fast path (no prefix swap page involved)
	 */
	if (end <= prefix || start >= prefix + 2 * PAGE_SIZE) {
		gmap_discard(vcpu->arch.gmap, start, end);
	} else {
		/*
		 * This is slow path.  gmap_discard will check for start
		 * so lets split this into before prefix, prefix, after
		 * prefix and let gmap_discard make some of these calls
		 * NOPs.
		 */
		gmap_discard(vcpu->arch.gmap, start, prefix);
		if (start <= prefix)
			gmap_discard(vcpu->arch.gmap, 0, PAGE_SIZE);
		if (end > prefix + PAGE_SIZE)
			gmap_discard(vcpu->arch.gmap, PAGE_SIZE, 2 * PAGE_SIZE);
		gmap_discard(vcpu->arch.gmap, prefix + 2 * PAGE_SIZE, end);
	}
	return 0;
}