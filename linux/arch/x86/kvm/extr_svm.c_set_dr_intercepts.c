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
struct TYPE_2__ {int intercept_dr; } ;
struct vmcb {TYPE_1__ control; } ;
struct vcpu_svm {int dummy; } ;

/* Variables and functions */
 int INTERCEPT_DR0_READ ; 
 int INTERCEPT_DR0_WRITE ; 
 int INTERCEPT_DR1_READ ; 
 int INTERCEPT_DR1_WRITE ; 
 int INTERCEPT_DR2_READ ; 
 int INTERCEPT_DR2_WRITE ; 
 int INTERCEPT_DR3_READ ; 
 int INTERCEPT_DR3_WRITE ; 
 int INTERCEPT_DR4_READ ; 
 int INTERCEPT_DR4_WRITE ; 
 int INTERCEPT_DR5_READ ; 
 int INTERCEPT_DR5_WRITE ; 
 int INTERCEPT_DR6_READ ; 
 int INTERCEPT_DR6_WRITE ; 
 int INTERCEPT_DR7_READ ; 
 int INTERCEPT_DR7_WRITE ; 
 struct vmcb* get_host_vmcb (struct vcpu_svm*) ; 
 int /*<<< orphan*/  recalc_intercepts (struct vcpu_svm*) ; 

__attribute__((used)) static inline void set_dr_intercepts(struct vcpu_svm *svm)
{
	struct vmcb *vmcb = get_host_vmcb(svm);

	vmcb->control.intercept_dr = (1 << INTERCEPT_DR0_READ)
		| (1 << INTERCEPT_DR1_READ)
		| (1 << INTERCEPT_DR2_READ)
		| (1 << INTERCEPT_DR3_READ)
		| (1 << INTERCEPT_DR4_READ)
		| (1 << INTERCEPT_DR5_READ)
		| (1 << INTERCEPT_DR6_READ)
		| (1 << INTERCEPT_DR7_READ)
		| (1 << INTERCEPT_DR0_WRITE)
		| (1 << INTERCEPT_DR1_WRITE)
		| (1 << INTERCEPT_DR2_WRITE)
		| (1 << INTERCEPT_DR3_WRITE)
		| (1 << INTERCEPT_DR4_WRITE)
		| (1 << INTERCEPT_DR5_WRITE)
		| (1 << INTERCEPT_DR6_WRITE)
		| (1 << INTERCEPT_DR7_WRITE);

	recalc_intercepts(svm);
}