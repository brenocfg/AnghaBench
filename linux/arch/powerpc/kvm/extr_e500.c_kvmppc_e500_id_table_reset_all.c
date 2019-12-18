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
struct vcpu_id_table {int dummy; } ;
struct kvmppc_vcpu_e500 {int /*<<< orphan*/  idt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_e500_recalc_shadow_pid (struct kvmppc_vcpu_e500*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvmppc_e500_id_table_reset_all(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	memset(vcpu_e500->idt, 0, sizeof(struct vcpu_id_table));

	/* Update shadow pid when mappings are changed */
	kvmppc_e500_recalc_shadow_pid(vcpu_e500);
}