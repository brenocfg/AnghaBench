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
struct vt_kms_softc {struct drm_fb_helper* fb_helper; } ;
struct drm_fb_helper {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_restore_fbdev_mode (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vt_restore_fbdev_mode(void *arg, int pending)
{
	struct drm_fb_helper *fb_helper;
	struct vt_kms_softc *sc;

	sc = (struct vt_kms_softc *)arg;
	fb_helper = sc->fb_helper;
	sx_xlock(&fb_helper->dev->mode_config.mutex);
	drm_fb_helper_restore_fbdev_mode(fb_helper);
	sx_xunlock(&fb_helper->dev->mode_config.mutex);
}