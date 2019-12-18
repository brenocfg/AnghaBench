#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_vcore {int first_vcpuid; int /*<<< orphan*/  preempt_list; struct kvm* kvm; int /*<<< orphan*/  lpcr; int /*<<< orphan*/  preempt_tb; int /*<<< orphan*/  wq; int /*<<< orphan*/  stoltb_lock; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lpcr; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TB_NIL ; 
 int /*<<< orphan*/  init_swait_queue_head (int /*<<< orphan*/ *) ; 
 struct kvmppc_vcore* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kvmppc_vcore *kvmppc_vcore_create(struct kvm *kvm, int id)
{
	struct kvmppc_vcore *vcore;

	vcore = kzalloc(sizeof(struct kvmppc_vcore), GFP_KERNEL);

	if (vcore == NULL)
		return NULL;

	spin_lock_init(&vcore->lock);
	spin_lock_init(&vcore->stoltb_lock);
	init_swait_queue_head(&vcore->wq);
	vcore->preempt_tb = TB_NIL;
	vcore->lpcr = kvm->arch.lpcr;
	vcore->first_vcpuid = id;
	vcore->kvm = kvm;
	INIT_LIST_HEAD(&vcore->preempt_list);

	return vcore;
}