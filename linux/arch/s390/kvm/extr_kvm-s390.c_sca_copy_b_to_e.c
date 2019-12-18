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
struct esca_block {int /*<<< orphan*/ * cpu; int /*<<< orphan*/ * mcn; int /*<<< orphan*/  ipte_control; } ;
struct bsca_block {int /*<<< orphan*/ * cpu; int /*<<< orphan*/  mcn; int /*<<< orphan*/  ipte_control; } ;

/* Variables and functions */
 int KVM_S390_BSCA_CPU_SLOTS ; 
 int /*<<< orphan*/  sca_copy_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sca_copy_b_to_e(struct esca_block *d, struct bsca_block *s)
{
	int i;

	d->ipte_control = s->ipte_control;
	d->mcn[0] = s->mcn;
	for (i = 0; i < KVM_S390_BSCA_CPU_SLOTS; i++)
		sca_copy_entry(&d->cpu[i], &s->cpu[i]);
}