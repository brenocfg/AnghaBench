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
typedef  unsigned long u32 ;
struct TYPE_2__ {unsigned long shareable_bits; int /*<<< orphan*/  cbm_len; } ;
struct rdt_resource {TYPE_1__ cache; } ;
struct rdt_domain {unsigned long* ctrl_val; } ;
typedef  enum rdtgrp_mode { ____Placeholder_rdtgrp_mode } rdtgrp_mode ;

/* Variables and functions */
 int RDT_MODE_EXCLUSIVE ; 
 int RDT_MODE_PSEUDO_LOCKSETUP ; 
 scalar_t__ bitmap_intersects (unsigned long*,unsigned long*,int /*<<< orphan*/ ) ; 
 scalar_t__ closid_allocated (int) ; 
 int closids_supported () ; 
 int rdtgroup_mode_by_closid (int) ; 

__attribute__((used)) static bool __rdtgroup_cbm_overlaps(struct rdt_resource *r, struct rdt_domain *d,
				    unsigned long cbm, int closid, bool exclusive)
{
	enum rdtgrp_mode mode;
	unsigned long ctrl_b;
	u32 *ctrl;
	int i;

	/* Check for any overlap with regions used by hardware directly */
	if (!exclusive) {
		ctrl_b = r->cache.shareable_bits;
		if (bitmap_intersects(&cbm, &ctrl_b, r->cache.cbm_len))
			return true;
	}

	/* Check for overlap with other resource groups */
	ctrl = d->ctrl_val;
	for (i = 0; i < closids_supported(); i++, ctrl++) {
		ctrl_b = *ctrl;
		mode = rdtgroup_mode_by_closid(i);
		if (closid_allocated(i) && i != closid &&
		    mode != RDT_MODE_PSEUDO_LOCKSETUP) {
			if (bitmap_intersects(&cbm, &ctrl_b, r->cache.cbm_len)) {
				if (exclusive) {
					if (mode == RDT_MODE_EXCLUSIVE)
						return true;
					continue;
				}
				return true;
			}
		}
	}

	return false;
}