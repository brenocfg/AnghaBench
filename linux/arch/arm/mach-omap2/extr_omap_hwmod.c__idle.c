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
struct omap_hwmod {int flags; scalar_t__ _state; scalar_t__ clkdm; TYPE_1__* class; int /*<<< orphan*/  name; int /*<<< orphan*/  _int_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable_module ) (struct omap_hwmod*) ;} ;
struct TYPE_3__ {scalar_t__ sysc; } ;

/* Variables and functions */
 int EINVAL ; 
 int HWMOD_BLOCK_WFI ; 
 int HWMOD_CLKDM_NOAUTO ; 
 int HWMOD_NO_IDLE ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _HWMOD_SKIP_ENABLE ; 
 scalar_t__ _HWMOD_STATE_ENABLED ; 
 scalar_t__ _HWMOD_STATE_IDLE ; 
 scalar_t__ _are_all_hardreset_lines_asserted (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _del_initiator_dep (struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _disable_clocks (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _idle_sysc (struct omap_hwmod*) ; 
 int /*<<< orphan*/  clkdm_allow_idle (scalar_t__) ; 
 int /*<<< orphan*/  clkdm_deny_idle (scalar_t__) ; 
 int /*<<< orphan*/  clkdm_hwmod_disable (scalar_t__,struct omap_hwmod*) ; 
 int /*<<< orphan*/  cpu_idle_poll_ctrl (int) ; 
 int /*<<< orphan*/  mpu_oh ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ soc_ops ; 
 int /*<<< orphan*/  stub1 (struct omap_hwmod*) ; 

__attribute__((used)) static int _idle(struct omap_hwmod *oh)
{
	if (oh->flags & HWMOD_NO_IDLE) {
		oh->_int_flags |= _HWMOD_SKIP_ENABLE;
		return 0;
	}

	pr_debug("omap_hwmod: %s: idling\n", oh->name);

	if (_are_all_hardreset_lines_asserted(oh))
		return 0;

	if (oh->_state != _HWMOD_STATE_ENABLED) {
		WARN(1, "omap_hwmod: %s: idle state can only be entered from enabled state\n",
			oh->name);
		return -EINVAL;
	}

	if (oh->class->sysc)
		_idle_sysc(oh);
	_del_initiator_dep(oh, mpu_oh);

	/*
	 * If HWMOD_CLKDM_NOAUTO is set then we don't
	 * deny idle the clkdm again since idle was already denied
	 * in _enable()
	 */
	if (oh->clkdm && !(oh->flags & HWMOD_CLKDM_NOAUTO))
		clkdm_deny_idle(oh->clkdm);

	if (oh->flags & HWMOD_BLOCK_WFI)
		cpu_idle_poll_ctrl(false);
	if (soc_ops.disable_module)
		soc_ops.disable_module(oh);

	/*
	 * The module must be in idle mode before disabling any parents
	 * clocks. Otherwise, the parent clock might be disabled before
	 * the module transition is done, and thus will prevent the
	 * transition to complete properly.
	 */
	_disable_clocks(oh);
	if (oh->clkdm) {
		clkdm_allow_idle(oh->clkdm);
		clkdm_hwmod_disable(oh->clkdm, oh);
	}

	oh->_state = _HWMOD_STATE_IDLE;

	return 0;
}