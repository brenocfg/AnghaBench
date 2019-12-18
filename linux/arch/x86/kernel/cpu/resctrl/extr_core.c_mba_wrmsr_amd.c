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
struct rdt_resource {scalar_t__ msr_base; } ;
struct rdt_domain {int /*<<< orphan*/ * ctrl_val; } ;
struct msr_param {unsigned int low; unsigned int high; } ;

/* Variables and functions */
 int /*<<< orphan*/  wrmsrl (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mba_wrmsr_amd(struct rdt_domain *d, struct msr_param *m, struct rdt_resource *r)
{
	unsigned int i;

	for (i = m->low; i < m->high; i++)
		wrmsrl(r->msr_base + i, d->ctrl_val[i]);
}