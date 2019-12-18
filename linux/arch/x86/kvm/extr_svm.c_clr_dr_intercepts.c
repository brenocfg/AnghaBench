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
struct TYPE_2__ {scalar_t__ intercept_dr; } ;
struct vmcb {TYPE_1__ control; } ;
struct vcpu_svm {int dummy; } ;

/* Variables and functions */
 struct vmcb* get_host_vmcb (struct vcpu_svm*) ; 
 int /*<<< orphan*/  recalc_intercepts (struct vcpu_svm*) ; 

__attribute__((used)) static inline void clr_dr_intercepts(struct vcpu_svm *svm)
{
	struct vmcb *vmcb = get_host_vmcb(svm);

	vmcb->control.intercept_dr = 0;

	recalc_intercepts(svm);
}