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
struct vm {int /*<<< orphan*/  cookie; struct vcpu* vcpu; } ;
struct vcpu {int /*<<< orphan*/  guestfpu; int /*<<< orphan*/  stats; int /*<<< orphan*/  vlapic; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLAPIC_CLEANUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_save_area_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vcpu_cleanup(struct vm *vm, int i, bool destroy)
{
	struct vcpu *vcpu = &vm->vcpu[i];

	VLAPIC_CLEANUP(vm->cookie, vcpu->vlapic);
	if (destroy) {
		vmm_stat_free(vcpu->stats);	
		fpu_save_area_free(vcpu->guestfpu);
	}
}