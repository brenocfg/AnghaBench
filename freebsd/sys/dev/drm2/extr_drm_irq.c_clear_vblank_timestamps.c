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
struct timeval {int dummy; } ;
struct drm_device {int /*<<< orphan*/ * _vblank_time; } ;

/* Variables and functions */
 int DRM_VBLANKTIME_RBSIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_vblank_timestamps(struct drm_device *dev, int crtc)
{
	memset(&dev->_vblank_time[crtc * DRM_VBLANKTIME_RBSIZE], 0,
		DRM_VBLANKTIME_RBSIZE * sizeof(struct timeval));
}