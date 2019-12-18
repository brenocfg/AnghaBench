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
typedef  int u32 ;
struct TYPE_4__ {int shareable_bits; scalar_t__ min_cbm_bits; int /*<<< orphan*/  cbm_len; } ;
struct rdt_resource {int /*<<< orphan*/  name; TYPE_2__ cache; } ;
struct rdt_domain {int have_new_ctrl; int new_ctrl; int* ctrl_val; int /*<<< orphan*/  id; TYPE_1__* plr; } ;
typedef  enum rdtgrp_mode { ____Placeholder_rdtgrp_mode } rdtgrp_mode ;
struct TYPE_3__ {int cbm; } ;

/* Variables and functions */
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int RDT_MODE_PSEUDO_LOCKSETUP ; 
 int RDT_MODE_SHAREABLE ; 
 scalar_t__ bitmap_weight (unsigned long*,int /*<<< orphan*/ ) ; 
 int cbm_ensure_valid (int,struct rdt_resource*) ; 
 scalar_t__ closid_allocated (int) ; 
 int closids_supported () ; 
 int /*<<< orphan*/  rdt_cdp_peer_get (struct rdt_resource*,struct rdt_domain*,struct rdt_resource**,struct rdt_domain**) ; 
 int /*<<< orphan*/  rdt_last_cmd_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdtgroup_mode_by_closid (int) ; 

__attribute__((used)) static int __init_one_rdt_domain(struct rdt_domain *d, struct rdt_resource *r,
				 u32 closid)
{
	struct rdt_resource *r_cdp = NULL;
	struct rdt_domain *d_cdp = NULL;
	u32 used_b = 0, unused_b = 0;
	unsigned long tmp_cbm;
	enum rdtgrp_mode mode;
	u32 peer_ctl, *ctrl;
	int i;

	rdt_cdp_peer_get(r, d, &r_cdp, &d_cdp);
	d->have_new_ctrl = false;
	d->new_ctrl = r->cache.shareable_bits;
	used_b = r->cache.shareable_bits;
	ctrl = d->ctrl_val;
	for (i = 0; i < closids_supported(); i++, ctrl++) {
		if (closid_allocated(i) && i != closid) {
			mode = rdtgroup_mode_by_closid(i);
			if (mode == RDT_MODE_PSEUDO_LOCKSETUP)
				/*
				 * ctrl values for locksetup aren't relevant
				 * until the schemata is written, and the mode
				 * becomes RDT_MODE_PSEUDO_LOCKED.
				 */
				continue;
			/*
			 * If CDP is active include peer domain's
			 * usage to ensure there is no overlap
			 * with an exclusive group.
			 */
			if (d_cdp)
				peer_ctl = d_cdp->ctrl_val[i];
			else
				peer_ctl = 0;
			used_b |= *ctrl | peer_ctl;
			if (mode == RDT_MODE_SHAREABLE)
				d->new_ctrl |= *ctrl | peer_ctl;
		}
	}
	if (d->plr && d->plr->cbm > 0)
		used_b |= d->plr->cbm;
	unused_b = used_b ^ (BIT_MASK(r->cache.cbm_len) - 1);
	unused_b &= BIT_MASK(r->cache.cbm_len) - 1;
	d->new_ctrl |= unused_b;
	/*
	 * Force the initial CBM to be valid, user can
	 * modify the CBM based on system availability.
	 */
	d->new_ctrl = cbm_ensure_valid(d->new_ctrl, r);
	/*
	 * Assign the u32 CBM to an unsigned long to ensure that
	 * bitmap_weight() does not access out-of-bound memory.
	 */
	tmp_cbm = d->new_ctrl;
	if (bitmap_weight(&tmp_cbm, r->cache.cbm_len) < r->cache.min_cbm_bits) {
		rdt_last_cmd_printf("No space on %s:%d\n", r->name, d->id);
		return -ENOSPC;
	}
	d->have_new_ctrl = true;

	return 0;
}