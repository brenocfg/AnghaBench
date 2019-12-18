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
struct TYPE_2__ {int /*<<< orphan*/ * kvm_split_mode; int /*<<< orphan*/ * kvm_vcore; int /*<<< orphan*/ * kvm_vcpu; scalar_t__ hwthread_req; } ;
struct paca_struct {TYPE_1__ kvm_hstate; } ;

/* Variables and functions */
 struct paca_struct** paca_ptrs ; 

__attribute__((used)) static void kvmppc_release_hwthread(int cpu)
{
	struct paca_struct *tpaca;

	tpaca = paca_ptrs[cpu];
	tpaca->kvm_hstate.hwthread_req = 0;
	tpaca->kvm_hstate.kvm_vcpu = NULL;
	tpaca->kvm_hstate.kvm_vcore = NULL;
	tpaca->kvm_hstate.kvm_split_mode = NULL;
}