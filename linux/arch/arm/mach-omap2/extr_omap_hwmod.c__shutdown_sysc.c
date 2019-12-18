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
struct omap_hwmod {TYPE_2__* class; int /*<<< orphan*/  _sysc_cache; } ;
struct TYPE_4__ {TYPE_1__* sysc; } ;
struct TYPE_3__ {int sysc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWMOD_IDLEMODE_FORCE ; 
 int SYSC_HAS_AUTOIDLE ; 
 int SYSC_HAS_MIDLEMODE ; 
 int SYSC_HAS_SIDLEMODE ; 
 int /*<<< orphan*/  _set_master_standbymode (struct omap_hwmod*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _set_module_autoidle (struct omap_hwmod*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _set_slave_idlemode (struct omap_hwmod*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _write_sysconfig (int /*<<< orphan*/ ,struct omap_hwmod*) ; 

__attribute__((used)) static void _shutdown_sysc(struct omap_hwmod *oh)
{
	u32 v;
	u8 sf;

	if (!oh->class->sysc)
		return;

	v = oh->_sysc_cache;
	sf = oh->class->sysc->sysc_flags;

	if (sf & SYSC_HAS_SIDLEMODE)
		_set_slave_idlemode(oh, HWMOD_IDLEMODE_FORCE, &v);

	if (sf & SYSC_HAS_MIDLEMODE)
		_set_master_standbymode(oh, HWMOD_IDLEMODE_FORCE, &v);

	if (sf & SYSC_HAS_AUTOIDLE)
		_set_module_autoidle(oh, 1, &v);

	_write_sysconfig(v, oh);
}