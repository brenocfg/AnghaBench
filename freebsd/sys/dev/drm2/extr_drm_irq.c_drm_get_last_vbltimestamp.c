#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct timeval {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* get_vblank_timestamp ) (struct drm_device*,int,int*,struct timeval*,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ drm_timestamp_precision ; 
 struct timeval get_drm_timestamp () ; 
 int stub1 (struct drm_device*,int,int*,struct timeval*,unsigned int) ; 

u32 drm_get_last_vbltimestamp(struct drm_device *dev, int crtc,
			      struct timeval *tvblank, unsigned flags)
{
	int ret;

	/* Define requested maximum error on timestamps (nanoseconds). */
	int max_error = (int) drm_timestamp_precision * 1000;

	/* Query driver if possible and precision timestamping enabled. */
	if (dev->driver->get_vblank_timestamp && (max_error > 0)) {
		ret = dev->driver->get_vblank_timestamp(dev, crtc, &max_error,
							tvblank, flags);
		if (ret > 0)
			return (u32) ret;
	}

	/* GPU high precision timestamp query unsupported or failed.
	 * Return current monotonic/gettimeofday timestamp as best estimate.
	 */
	*tvblank = get_drm_timestamp();

	return 0;
}