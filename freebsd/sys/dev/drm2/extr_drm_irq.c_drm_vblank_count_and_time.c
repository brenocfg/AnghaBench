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
typedef  scalar_t__ u32 ;
struct timeval {int dummy; } ;
struct drm_device {int /*<<< orphan*/ * _vblank_count; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 struct timeval vblanktimestamp (struct drm_device*,int,scalar_t__) ; 

u32 drm_vblank_count_and_time(struct drm_device *dev, int crtc,
			      struct timeval *vblanktime)
{
	u32 cur_vblank;

	/* Read timestamp from slot of _vblank_time ringbuffer
	 * that corresponds to current vblank count. Retry if
	 * count has incremented during readout. This works like
	 * a seqlock.
	 */
	do {
		cur_vblank = atomic_read(&dev->_vblank_count[crtc]);
		*vblanktime = vblanktimestamp(dev, crtc, cur_vblank);
		smp_rmb();
	} while (cur_vblank != atomic_read(&dev->_vblank_count[crtc]));

	return cur_vblank;
}