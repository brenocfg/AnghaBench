#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmcb_seg {int dummy; } ;
struct vmcb_save_area {struct vmcb_seg ldtr; struct vmcb_seg tr; struct vmcb_seg ss; struct vmcb_seg gs; struct vmcb_seg fs; struct vmcb_seg es; struct vmcb_seg ds; struct vmcb_seg cs; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vmcb; } ;
struct TYPE_3__ {struct vmcb_save_area save; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  VCPU_SREG_CS 135 
#define  VCPU_SREG_DS 134 
#define  VCPU_SREG_ES 133 
#define  VCPU_SREG_FS 132 
#define  VCPU_SREG_GS 131 
#define  VCPU_SREG_LDTR 130 
#define  VCPU_SREG_SS 129 
#define  VCPU_SREG_TR 128 
 TYPE_2__* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static struct vmcb_seg *svm_seg(struct kvm_vcpu *vcpu, int seg)
{
	struct vmcb_save_area *save = &to_svm(vcpu)->vmcb->save;

	switch (seg) {
	case VCPU_SREG_CS: return &save->cs;
	case VCPU_SREG_DS: return &save->ds;
	case VCPU_SREG_ES: return &save->es;
	case VCPU_SREG_FS: return &save->fs;
	case VCPU_SREG_GS: return &save->gs;
	case VCPU_SREG_SS: return &save->ss;
	case VCPU_SREG_TR: return &save->tr;
	case VCPU_SREG_LDTR: return &save->ldtr;
	}
	BUG();
	return NULL;
}