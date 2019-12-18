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
struct vcpu_svm {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int kvm_emulate_instruction_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsm_ins_bytes ; 

__attribute__((used)) static int rsm_interception(struct vcpu_svm *svm)
{
	return kvm_emulate_instruction_from_buffer(&svm->vcpu, rsm_ins_bytes, 2);
}