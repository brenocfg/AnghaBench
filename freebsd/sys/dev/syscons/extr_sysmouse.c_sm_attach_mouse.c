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
 int /*<<< orphan*/  VTY_SC ; 
 int /*<<< orphan*/  smdev_evdev_init () ; 
 int /*<<< orphan*/  smdev_ttydevsw ; 
 int /*<<< orphan*/  sysmouse_tty ; 
 int /*<<< orphan*/  tty_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sm_attach_mouse(void *unused)
{
	if (!vty_enabled(VTY_SC))
		return;
	sysmouse_tty = tty_alloc(&smdev_ttydevsw, NULL);
	tty_makedev(sysmouse_tty, NULL, "sysmouse");
#ifdef EVDEV_SUPPORT
	smdev_evdev_init();
#endif
}