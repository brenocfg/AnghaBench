#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {unsigned long itdba; unsigned int icpua; int /*<<< orphan*/  gd; int /*<<< orphan*/  msl; scalar_t__ mso; } ;
struct sie_page {int /*<<< orphan*/  itdb; TYPE_5__ sie_block; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {TYPE_5__* sie_block; int /*<<< orphan*/  cputm_seqcount; TYPE_1__ local_int; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct TYPE_9__ {scalar_t__ origin; } ;
struct TYPE_10__ {TYPE_2__ gisa_int; } ;
struct kvm {TYPE_3__ arch; } ;
struct TYPE_13__ {scalar_t__ has_gisaf; int /*<<< orphan*/  hamax; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct kvm_vcpu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GISA_FORMAT1 ; 
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,unsigned int,struct kvm_vcpu*,TYPE_5__*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 struct kvm_vcpu* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_ucontrol (struct kvm*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int kvm_vcpu_init (struct kvm_vcpu*,struct kvm*,unsigned int) ; 
 int /*<<< orphan*/  sca_can_add_vcpu (struct kvm*,unsigned int) ; 
 TYPE_6__ sclp ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvm_s390_create_vcpu (unsigned int,struct kvm_vcpu*,TYPE_5__*) ; 

struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm,
				      unsigned int id)
{
	struct kvm_vcpu *vcpu;
	struct sie_page *sie_page;
	int rc = -EINVAL;

	if (!kvm_is_ucontrol(kvm) && !sca_can_add_vcpu(kvm, id))
		goto out;

	rc = -ENOMEM;

	vcpu = kmem_cache_zalloc(kvm_vcpu_cache, GFP_KERNEL);
	if (!vcpu)
		goto out;

	BUILD_BUG_ON(sizeof(struct sie_page) != 4096);
	sie_page = (struct sie_page *) get_zeroed_page(GFP_KERNEL);
	if (!sie_page)
		goto out_free_cpu;

	vcpu->arch.sie_block = &sie_page->sie_block;
	vcpu->arch.sie_block->itdba = (unsigned long) &sie_page->itdb;

	/* the real guest size will always be smaller than msl */
	vcpu->arch.sie_block->mso = 0;
	vcpu->arch.sie_block->msl = sclp.hamax;

	vcpu->arch.sie_block->icpua = id;
	spin_lock_init(&vcpu->arch.local_int.lock);
	vcpu->arch.sie_block->gd = (u32)(u64)kvm->arch.gisa_int.origin;
	if (vcpu->arch.sie_block->gd && sclp.has_gisaf)
		vcpu->arch.sie_block->gd |= GISA_FORMAT1;
	seqcount_init(&vcpu->arch.cputm_seqcount);

	rc = kvm_vcpu_init(vcpu, kvm, id);
	if (rc)
		goto out_free_sie_block;
	VM_EVENT(kvm, 3, "create cpu %d at 0x%pK, sie block at 0x%pK", id, vcpu,
		 vcpu->arch.sie_block);
	trace_kvm_s390_create_vcpu(id, vcpu, vcpu->arch.sie_block);

	return vcpu;
out_free_sie_block:
	free_page((unsigned long)(vcpu->arch.sie_block));
out_free_cpu:
	kmem_cache_free(kvm_vcpu_cache, vcpu);
out:
	return ERR_PTR(rc);
}