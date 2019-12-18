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
typedef  int /*<<< orphan*/  u32 ;
struct rdtgroup {scalar_t__ mode; int /*<<< orphan*/  closid; } ;
struct rdt_resource {int /*<<< orphan*/  (* cbm_validate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rdt_resource*) ;} ;
struct rdt_parse_data {int /*<<< orphan*/  buf; struct rdtgroup* rdtgrp; } ;
struct rdt_domain {int have_new_ctrl; int /*<<< orphan*/  new_ctrl; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RDT_MODE_EXCLUSIVE ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKSETUP ; 
 scalar_t__ RDT_MODE_SHAREABLE ; 
 int /*<<< orphan*/  rdt_last_cmd_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 scalar_t__ rdtgroup_cbm_overlaps (struct rdt_resource*,struct rdt_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdtgroup_cbm_overlaps_pseudo_locked (struct rdt_domain*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdtgroup_pseudo_locked_in_hierarchy (struct rdt_domain*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rdt_resource*) ; 

int parse_cbm(struct rdt_parse_data *data, struct rdt_resource *r,
	      struct rdt_domain *d)
{
	struct rdtgroup *rdtgrp = data->rdtgrp;
	u32 cbm_val;

	if (d->have_new_ctrl) {
		rdt_last_cmd_printf("Duplicate domain %d\n", d->id);
		return -EINVAL;
	}

	/*
	 * Cannot set up more than one pseudo-locked region in a cache
	 * hierarchy.
	 */
	if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP &&
	    rdtgroup_pseudo_locked_in_hierarchy(d)) {
		rdt_last_cmd_puts("Pseudo-locked region in hierarchy\n");
		return -EINVAL;
	}

	if (!r->cbm_validate(data->buf, &cbm_val, r))
		return -EINVAL;

	if ((rdtgrp->mode == RDT_MODE_EXCLUSIVE ||
	     rdtgrp->mode == RDT_MODE_SHAREABLE) &&
	    rdtgroup_cbm_overlaps_pseudo_locked(d, cbm_val)) {
		rdt_last_cmd_puts("CBM overlaps with pseudo-locked region\n");
		return -EINVAL;
	}

	/*
	 * The CBM may not overlap with the CBM of another closid if
	 * either is exclusive.
	 */
	if (rdtgroup_cbm_overlaps(r, d, cbm_val, rdtgrp->closid, true)) {
		rdt_last_cmd_puts("Overlaps with exclusive group\n");
		return -EINVAL;
	}

	if (rdtgroup_cbm_overlaps(r, d, cbm_val, rdtgrp->closid, false)) {
		if (rdtgrp->mode == RDT_MODE_EXCLUSIVE ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) {
			rdt_last_cmd_puts("Overlaps with other group\n");
			return -EINVAL;
		}
	}

	d->new_ctrl = cbm_val;
	d->have_new_ctrl = true;

	return 0;
}