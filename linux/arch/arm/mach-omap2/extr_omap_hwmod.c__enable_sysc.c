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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct omap_hwmod {int flags; TYPE_2__* class; int /*<<< orphan*/  _sysc_cache; } ;
struct clockdomain {int flags; } ;
struct TYPE_4__ {TYPE_1__* sysc; } ;
struct TYPE_3__ {int sysc_flags; int idlemodes; } ;

/* Variables and functions */
 int CLKDM_ACTIVE_WITH_MPU ; 
 int /*<<< orphan*/  CLOCKACT_TEST_ICLK ; 
 int HWMOD_CONTROL_OPT_CLKS_IN_RESET ; 
 int HWMOD_FORCE_MSTANDBY ; 
 int HWMOD_IDLEMODE_FORCE ; 
 int HWMOD_IDLEMODE_NO ; 
 int HWMOD_IDLEMODE_SMART ; 
 int HWMOD_IDLEMODE_SMART_WKUP ; 
 int HWMOD_NO_OCP_AUTOIDLE ; 
 int HWMOD_SET_DEFAULT_CLOCKACT ; 
 int HWMOD_SWSUP_MSTANDBY ; 
 int HWMOD_SWSUP_SIDLE ; 
 int HWMOD_SWSUP_SIDLE_ACT ; 
 int MSTANDBY_SMART_WKUP ; 
 int SIDLE_SMART ; 
 int SIDLE_SMART_WKUP ; 
 int SYSC_HAS_AUTOIDLE ; 
 int SYSC_HAS_CLOCKACTIVITY ; 
 int SYSC_HAS_ENAWAKEUP ; 
 int SYSC_HAS_MIDLEMODE ; 
 int SYSC_HAS_SIDLEMODE ; 
 int /*<<< orphan*/  _disable_optional_clocks (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _enable_optional_clocks (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _enable_wakeup (struct omap_hwmod*,int /*<<< orphan*/ *) ; 
 struct clockdomain* _get_clkdm (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _set_clockactivity (struct omap_hwmod*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _set_master_standbymode (struct omap_hwmod*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _set_module_autoidle (struct omap_hwmod*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _set_slave_idlemode (struct omap_hwmod*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _wait_softreset_complete (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _write_sysconfig (int /*<<< orphan*/ ,struct omap_hwmod*) ; 

__attribute__((used)) static void _enable_sysc(struct omap_hwmod *oh)
{
	u8 idlemode, sf;
	u32 v;
	bool clkdm_act;
	struct clockdomain *clkdm;

	if (!oh->class->sysc)
		return;

	/*
	 * Wait until reset has completed, this is needed as the IP
	 * block is reset automatically by hardware in some cases
	 * (off-mode for example), and the drivers require the
	 * IP to be ready when they access it
	 */
	if (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_enable_optional_clocks(oh);
	_wait_softreset_complete(oh);
	if (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_disable_optional_clocks(oh);

	v = oh->_sysc_cache;
	sf = oh->class->sysc->sysc_flags;

	clkdm = _get_clkdm(oh);
	if (sf & SYSC_HAS_SIDLEMODE) {
		if (oh->flags & HWMOD_SWSUP_SIDLE ||
		    oh->flags & HWMOD_SWSUP_SIDLE_ACT) {
			idlemode = HWMOD_IDLEMODE_NO;
		} else {
			if (sf & SYSC_HAS_ENAWAKEUP)
				_enable_wakeup(oh, &v);
			if (oh->class->sysc->idlemodes & SIDLE_SMART_WKUP)
				idlemode = HWMOD_IDLEMODE_SMART_WKUP;
			else
				idlemode = HWMOD_IDLEMODE_SMART;
		}

		/*
		 * This is special handling for some IPs like
		 * 32k sync timer. Force them to idle!
		 */
		clkdm_act = (clkdm && clkdm->flags & CLKDM_ACTIVE_WITH_MPU);
		if (clkdm_act && !(oh->class->sysc->idlemodes &
				   (SIDLE_SMART | SIDLE_SMART_WKUP)))
			idlemode = HWMOD_IDLEMODE_FORCE;

		_set_slave_idlemode(oh, idlemode, &v);
	}

	if (sf & SYSC_HAS_MIDLEMODE) {
		if (oh->flags & HWMOD_FORCE_MSTANDBY) {
			idlemode = HWMOD_IDLEMODE_FORCE;
		} else if (oh->flags & HWMOD_SWSUP_MSTANDBY) {
			idlemode = HWMOD_IDLEMODE_NO;
		} else {
			if (sf & SYSC_HAS_ENAWAKEUP)
				_enable_wakeup(oh, &v);
			if (oh->class->sysc->idlemodes & MSTANDBY_SMART_WKUP)
				idlemode = HWMOD_IDLEMODE_SMART_WKUP;
			else
				idlemode = HWMOD_IDLEMODE_SMART;
		}
		_set_master_standbymode(oh, idlemode, &v);
	}

	/*
	 * XXX The clock framework should handle this, by
	 * calling into this code.  But this must wait until the
	 * clock structures are tagged with omap_hwmod entries
	 */
	if ((oh->flags & HWMOD_SET_DEFAULT_CLOCKACT) &&
	    (sf & SYSC_HAS_CLOCKACTIVITY))
		_set_clockactivity(oh, CLOCKACT_TEST_ICLK, &v);

	_write_sysconfig(v, oh);

	/*
	 * Set the autoidle bit only after setting the smartidle bit
	 * Setting this will not have any impact on the other modules.
	 */
	if (sf & SYSC_HAS_AUTOIDLE) {
		idlemode = (oh->flags & HWMOD_NO_OCP_AUTOIDLE) ?
			0 : 1;
		_set_module_autoidle(oh, idlemode, &v);
		_write_sysconfig(v, oh);
	}
}