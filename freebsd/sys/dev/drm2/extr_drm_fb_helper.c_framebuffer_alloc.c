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
struct vt_kms_softc {int /*<<< orphan*/  fb_mode_task; } ;
struct fb_info {int /*<<< orphan*/ * enter; struct vt_kms_softc* fb_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_KMS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vt_kms_softc*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vt_kms_postswitch ; 
 int /*<<< orphan*/  vt_restore_fbdev_mode ; 

struct fb_info *
framebuffer_alloc()
{
	struct fb_info *info;
	struct vt_kms_softc *sc;

	info = malloc(sizeof(*info), DRM_MEM_KMS, M_WAITOK | M_ZERO);

	sc = malloc(sizeof(*sc), DRM_MEM_KMS, M_WAITOK | M_ZERO);
	TASK_INIT(&sc->fb_mode_task, 0, vt_restore_fbdev_mode, sc);

	info->fb_priv = sc;
	info->enter = &vt_kms_postswitch;

	return (info);
}