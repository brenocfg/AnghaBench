#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int hflags; } ;
struct TYPE_8__ {TYPE_3__ arch; } ;
struct vcpu_svm {TYPE_4__ vcpu; TYPE_2__* vmcb; } ;
struct TYPE_5__ {int int_ctl; } ;
struct TYPE_6__ {TYPE_1__ control; } ;

/* Variables and functions */
 int HF_GIF_MASK ; 
 int V_GIF_MASK ; 
 scalar_t__ vgif_enabled (struct vcpu_svm*) ; 

__attribute__((used)) static inline bool gif_set(struct vcpu_svm *svm)
{
	if (vgif_enabled(svm))
		return !!(svm->vmcb->control.int_ctl & V_GIF_MASK);
	else
		return !!(svm->vcpu.arch.hflags & HF_GIF_MASK);
}