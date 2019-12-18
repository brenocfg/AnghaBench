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
struct kvm_vcpu {TYPE_2__* run; struct kvm_mmio_fragment* mmio_fragments; } ;
struct kvm_mmio_fragment {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ mmio; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_exit_mmio(struct kvm_vcpu *vcpu, gpa_t gpa,
			   void *val, int bytes)
{
	struct kvm_mmio_fragment *frag = &vcpu->mmio_fragments[0];

	memcpy(vcpu->run->mmio.data, frag->data, min(8u, frag->len));
	return X86EMUL_CONTINUE;
}