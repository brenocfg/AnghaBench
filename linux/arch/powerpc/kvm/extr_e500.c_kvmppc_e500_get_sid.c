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
struct vcpu_id_table {int /*<<< orphan*/ *** id; } ;
struct kvmppc_vcpu_e500 {struct vcpu_id_table* idt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int NUM_TIDS ; 
 int /*<<< orphan*/  _tlbil_all () ; 
 int /*<<< orphan*/  kvmppc_e500_recalc_shadow_pid (struct kvmppc_vcpu_e500*) ; 
 int /*<<< orphan*/  local_sid_destroy_all () ; 
 int local_sid_lookup (int /*<<< orphan*/ *) ; 
 int local_sid_setup_one (int /*<<< orphan*/ *) ; 

unsigned int kvmppc_e500_get_sid(struct kvmppc_vcpu_e500 *vcpu_e500,
				 unsigned int as, unsigned int gid,
				 unsigned int pr, int avoid_recursion)
{
	struct vcpu_id_table *idt = vcpu_e500->idt;
	int sid;

	BUG_ON(as >= 2);
	BUG_ON(gid >= NUM_TIDS);
	BUG_ON(pr >= 2);

	sid = local_sid_lookup(&idt->id[as][gid][pr]);

	while (sid <= 0) {
		/* No mapping yet */
		sid = local_sid_setup_one(&idt->id[as][gid][pr]);
		if (sid <= 0) {
			_tlbil_all();
			local_sid_destroy_all();
		}

		/* Update shadow pid when mappings are changed */
		if (!avoid_recursion)
			kvmppc_e500_recalc_shadow_pid(vcpu_e500);
	}

	return sid;
}