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
struct kvmppc_vcore {int num_threads; scalar_t__ kvm; int /*<<< orphan*/  preempt_list; } ;
struct core_info {int max_subcore_threads; int n_subcores; int total_threads; int* subcore_threads; struct kvmppc_vcore** vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_vcore_to_run (struct kvmppc_vcore*) ; 
 scalar_t__ kvm_is_radix (scalar_t__) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ no_mixing_hpt_and_radix ; 
 scalar_t__ one_vm_per_core ; 
 int /*<<< orphan*/  subcore_config_ok (int,int) ; 

__attribute__((used)) static bool can_dynamic_split(struct kvmppc_vcore *vc, struct core_info *cip)
{
	int n_threads = vc->num_threads;
	int sub;

	if (!cpu_has_feature(CPU_FTR_ARCH_207S))
		return false;

	/* In one_vm_per_core mode, require all vcores to be from the same vm */
	if (one_vm_per_core && vc->kvm != cip->vc[0]->kvm)
		return false;

	/* Some POWER9 chips require all threads to be in the same MMU mode */
	if (no_mixing_hpt_and_radix &&
	    kvm_is_radix(vc->kvm) != kvm_is_radix(cip->vc[0]->kvm))
		return false;

	if (n_threads < cip->max_subcore_threads)
		n_threads = cip->max_subcore_threads;
	if (!subcore_config_ok(cip->n_subcores + 1, n_threads))
		return false;
	cip->max_subcore_threads = n_threads;

	sub = cip->n_subcores;
	++cip->n_subcores;
	cip->total_threads += vc->num_threads;
	cip->subcore_threads[sub] = vc->num_threads;
	cip->vc[sub] = vc;
	init_vcore_to_run(vc);
	list_del_init(&vc->preempt_list);

	return true;
}