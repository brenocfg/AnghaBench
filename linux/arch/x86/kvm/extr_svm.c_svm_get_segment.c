#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vmcb_seg {int limit; int attrib; int /*<<< orphan*/  selector; int /*<<< orphan*/  base; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {int limit; int type; int s; int dpl; int present; int avl; int l; int db; int g; int unusable; int /*<<< orphan*/  selector; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {TYPE_2__* vmcb; } ;
struct TYPE_4__ {int cpl; } ;
struct TYPE_5__ {TYPE_1__ save; } ;

/* Variables and functions */
 int SVM_SELECTOR_AVL_SHIFT ; 
 int SVM_SELECTOR_DB_SHIFT ; 
 int SVM_SELECTOR_DPL_SHIFT ; 
 int SVM_SELECTOR_L_SHIFT ; 
 int SVM_SELECTOR_P_SHIFT ; 
 int SVM_SELECTOR_S_SHIFT ; 
 int SVM_SELECTOR_TYPE_MASK ; 
#define  VCPU_SREG_DS 133 
#define  VCPU_SREG_ES 132 
#define  VCPU_SREG_FS 131 
#define  VCPU_SREG_GS 130 
#define  VCPU_SREG_SS 129 
#define  VCPU_SREG_TR 128 
 struct vmcb_seg* svm_seg (struct kvm_vcpu*,int) ; 
 TYPE_3__* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_get_segment(struct kvm_vcpu *vcpu,
			    struct kvm_segment *var, int seg)
{
	struct vmcb_seg *s = svm_seg(vcpu, seg);

	var->base = s->base;
	var->limit = s->limit;
	var->selector = s->selector;
	var->type = s->attrib & SVM_SELECTOR_TYPE_MASK;
	var->s = (s->attrib >> SVM_SELECTOR_S_SHIFT) & 1;
	var->dpl = (s->attrib >> SVM_SELECTOR_DPL_SHIFT) & 3;
	var->present = (s->attrib >> SVM_SELECTOR_P_SHIFT) & 1;
	var->avl = (s->attrib >> SVM_SELECTOR_AVL_SHIFT) & 1;
	var->l = (s->attrib >> SVM_SELECTOR_L_SHIFT) & 1;
	var->db = (s->attrib >> SVM_SELECTOR_DB_SHIFT) & 1;

	/*
	 * AMD CPUs circa 2014 track the G bit for all segments except CS.
	 * However, the SVM spec states that the G bit is not observed by the
	 * CPU, and some VMware virtual CPUs drop the G bit for all segments.
	 * So let's synthesize a legal G bit for all segments, this helps
	 * running KVM nested. It also helps cross-vendor migration, because
	 * Intel's vmentry has a check on the 'G' bit.
	 */
	var->g = s->limit > 0xfffff;

	/*
	 * AMD's VMCB does not have an explicit unusable field, so emulate it
	 * for cross vendor migration purposes by "not present"
	 */
	var->unusable = !var->present;

	switch (seg) {
	case VCPU_SREG_TR:
		/*
		 * Work around a bug where the busy flag in the tr selector
		 * isn't exposed
		 */
		var->type |= 0x2;
		break;
	case VCPU_SREG_DS:
	case VCPU_SREG_ES:
	case VCPU_SREG_FS:
	case VCPU_SREG_GS:
		/*
		 * The accessed bit must always be set in the segment
		 * descriptor cache, although it can be cleared in the
		 * descriptor, the cached bit always remains at 1. Since
		 * Intel has a check on this, set it here to support
		 * cross-vendor migration.
		 */
		if (!var->unusable)
			var->type |= 0x1;
		break;
	case VCPU_SREG_SS:
		/*
		 * On AMD CPUs sometimes the DB bit in the segment
		 * descriptor is left as 1, although the whole segment has
		 * been made unusable. Clear it here to pass an Intel VMX
		 * entry check when cross vendor migrating.
		 */
		if (var->unusable)
			var->db = 0;
		/* This is symmetric with svm_set_segment() */
		var->dpl = to_svm(vcpu)->vmcb->save.cpl;
		break;
	}
}