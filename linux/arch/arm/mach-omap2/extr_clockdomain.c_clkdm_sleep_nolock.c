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
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
struct clockdomain {int flags; TYPE_1__ pwrdm; int /*<<< orphan*/  _flags; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int (* clkdm_sleep ) (struct clockdomain*) ;} ;

/* Variables and functions */
 int CLKDM_CAN_FORCE_SLEEP ; 
 int EINVAL ; 
 int /*<<< orphan*/  _CLKDM_FLAG_HWSUP_ENABLED ; 
 TYPE_2__* arch_clkdm ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int pwrdm_state_switch_nolock (int /*<<< orphan*/ ) ; 
 int stub1 (struct clockdomain*) ; 

int clkdm_sleep_nolock(struct clockdomain *clkdm)
{
	int ret;

	if (!clkdm)
		return -EINVAL;

	if (!(clkdm->flags & CLKDM_CAN_FORCE_SLEEP)) {
		pr_debug("clockdomain: %s does not support forcing sleep via software\n",
			 clkdm->name);
		return -EINVAL;
	}

	if (!arch_clkdm || !arch_clkdm->clkdm_sleep)
		return -EINVAL;

	pr_debug("clockdomain: forcing sleep on %s\n", clkdm->name);

	clkdm->_flags &= ~_CLKDM_FLAG_HWSUP_ENABLED;
	ret = arch_clkdm->clkdm_sleep(clkdm);
	ret |= pwrdm_state_switch_nolock(clkdm->pwrdm.ptr);

	return ret;
}