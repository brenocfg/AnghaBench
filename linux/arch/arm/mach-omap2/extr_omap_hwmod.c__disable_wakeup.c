#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct omap_hwmod {TYPE_3__* class; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__* sysc; } ;
struct TYPE_5__ {int sysc_flags; int idlemodes; TYPE_1__* sysc_fields; } ;
struct TYPE_4__ {int enwkup_shift; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HWMOD_IDLEMODE_SMART ; 
 int MSTANDBY_SMART_WKUP ; 
 int SIDLE_SMART_WKUP ; 
 int SYSC_HAS_ENAWAKEUP ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_master_standbymode (struct omap_hwmod*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _set_slave_idlemode (struct omap_hwmod*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int _disable_wakeup(struct omap_hwmod *oh, u32 *v)
{
	if (!oh->class->sysc ||
	    !((oh->class->sysc->sysc_flags & SYSC_HAS_ENAWAKEUP) ||
	      (oh->class->sysc->idlemodes & SIDLE_SMART_WKUP) ||
	      (oh->class->sysc->idlemodes & MSTANDBY_SMART_WKUP)))
		return -EINVAL;

	if (!oh->class->sysc->sysc_fields) {
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		return -EINVAL;
	}

	if (oh->class->sysc->sysc_flags & SYSC_HAS_ENAWAKEUP)
		*v &= ~(0x1 << oh->class->sysc->sysc_fields->enwkup_shift);

	if (oh->class->sysc->idlemodes & SIDLE_SMART_WKUP)
		_set_slave_idlemode(oh, HWMOD_IDLEMODE_SMART, v);
	if (oh->class->sysc->idlemodes & MSTANDBY_SMART_WKUP)
		_set_master_standbymode(oh, HWMOD_IDLEMODE_SMART, v);

	/* XXX test pwrdm_get_wken for this hwmod's subsystem */

	return 0;
}