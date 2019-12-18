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
typedef  int /*<<< orphan*/  ulong ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EMULATE_FAIL ; 

__attribute__((used)) static int kvmppc_core_emulate_mfspr_hv(struct kvm_vcpu *vcpu, int sprn,
					ulong *spr_val)
{
	return EMULATE_FAIL;
}