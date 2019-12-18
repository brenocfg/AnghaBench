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
struct vcpu_svm {int dummy; } ;

/* Variables and functions */
 scalar_t__ nested_svm_check_permissions (struct vcpu_svm*) ; 
 int nested_svm_vmrun (struct vcpu_svm*) ; 

__attribute__((used)) static int vmrun_interception(struct vcpu_svm *svm)
{
	if (nested_svm_check_permissions(svm))
		return 1;

	return nested_svm_vmrun(svm);
}