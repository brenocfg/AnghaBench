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
struct kvm_nested_guest {unsigned int l1_lpid; long shadow_lpid; int radix; int /*<<< orphan*/  shadow_pgtable; int /*<<< orphan*/  prev_cpu; int /*<<< orphan*/  tlb_lock; struct kvm* l1_host; } ;
struct kvm {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct kvm_nested_guest*) ; 
 long kvmppc_alloc_lpid () ; 
 struct kvm_nested_guest* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct kvm_nested_guest *kvmhv_alloc_nested(struct kvm *kvm, unsigned int lpid)
{
	struct kvm_nested_guest *gp;
	long shadow_lpid;

	gp = kzalloc(sizeof(*gp), GFP_KERNEL);
	if (!gp)
		return NULL;
	gp->l1_host = kvm;
	gp->l1_lpid = lpid;
	mutex_init(&gp->tlb_lock);
	gp->shadow_pgtable = pgd_alloc(kvm->mm);
	if (!gp->shadow_pgtable)
		goto out_free;
	shadow_lpid = kvmppc_alloc_lpid();
	if (shadow_lpid < 0)
		goto out_free2;
	gp->shadow_lpid = shadow_lpid;
	gp->radix = 1;

	memset(gp->prev_cpu, -1, sizeof(gp->prev_cpu));

	return gp;

 out_free2:
	pgd_free(kvm->mm, gp->shadow_pgtable);
 out_free:
	kfree(gp);
	return NULL;
}