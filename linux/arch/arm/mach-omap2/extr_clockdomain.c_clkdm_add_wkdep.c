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
struct clockdomain {int /*<<< orphan*/  wkdep_srcs; } ;
struct clkdm_dep {TYPE_2__* clkdm; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_4__ {TYPE_1__ pwrdm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clkdm_dep*) ; 
 int PTR_ERR (struct clkdm_dep*) ; 
 int _clkdm_add_wkdep (struct clockdomain*,struct clockdomain*) ; 
 struct clkdm_dep* _clkdm_deps_lookup (struct clockdomain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_unlock (int /*<<< orphan*/ ) ; 

int clkdm_add_wkdep(struct clockdomain *clkdm1, struct clockdomain *clkdm2)
{
	struct clkdm_dep *cd;
	int ret;

	if (!clkdm1 || !clkdm2)
		return -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	if (IS_ERR(cd))
		return PTR_ERR(cd);

	pwrdm_lock(cd->clkdm->pwrdm.ptr);
	ret = _clkdm_add_wkdep(clkdm1, clkdm2);
	pwrdm_unlock(cd->clkdm->pwrdm.ptr);

	return ret;
}