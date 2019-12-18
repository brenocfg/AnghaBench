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
struct omap_hwmod {int dummy; } ;
struct clockdomain {int flags; } ;

/* Variables and functions */
 int CLKDM_NO_AUTODEPS ; 
 int EINVAL ; 
 struct clockdomain* _get_clkdm (struct omap_hwmod*) ; 
 int clkdm_add_sleepdep (struct clockdomain*,struct clockdomain*) ; 

__attribute__((used)) static int _add_initiator_dep(struct omap_hwmod *oh, struct omap_hwmod *init_oh)
{
	struct clockdomain *clkdm, *init_clkdm;

	clkdm = _get_clkdm(oh);
	init_clkdm = _get_clkdm(init_oh);

	if (!clkdm || !init_clkdm)
		return -EINVAL;

	if (clkdm && clkdm->flags & CLKDM_NO_AUTODEPS)
		return 0;

	return clkdm_add_sleepdep(clkdm, init_clkdm);
}