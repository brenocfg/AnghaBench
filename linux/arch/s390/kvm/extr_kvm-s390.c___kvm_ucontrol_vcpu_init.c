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
struct TYPE_4__ {TYPE_2__* gmap; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
struct TYPE_6__ {int /*<<< orphan*/  mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_3__* current ; 
 TYPE_2__* gmap_create (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int __kvm_ucontrol_vcpu_init(struct kvm_vcpu *vcpu)
{
	vcpu->arch.gmap = gmap_create(current->mm, -1UL);
	if (!vcpu->arch.gmap)
		return -ENOMEM;
	vcpu->arch.gmap->private = vcpu->kvm;

	return 0;
}