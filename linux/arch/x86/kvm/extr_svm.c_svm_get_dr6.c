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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_6__ {TYPE_2__* vmcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  dr6; } ;
struct TYPE_5__ {TYPE_1__ save; } ;

/* Variables and functions */
 TYPE_3__* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static u64 svm_get_dr6(struct kvm_vcpu *vcpu)
{
	return to_svm(vcpu)->vmcb->save.dr6;
}