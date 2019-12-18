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

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  VTY_VT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysmouse_cdevsw ; 
 int /*<<< orphan*/  sysmouse_evdev_init () ; 
 int /*<<< orphan*/  sysmouse_lock ; 
 int /*<<< orphan*/  sysmouse_sleep ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sysmouse_drvinit(void *unused)
{

	if (!vty_enabled(VTY_VT))
		return;
	mtx_init(&sysmouse_lock, "sysmouse", NULL, MTX_DEF);
	cv_init(&sysmouse_sleep, "sysmrd");
	make_dev(&sysmouse_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600,
	    "sysmouse");
#ifdef EVDEV_SUPPORT
	sysmouse_evdev_init();
#endif
}