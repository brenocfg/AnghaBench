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
struct TYPE_2__ {int /*<<< orphan*/  reg_a; } ;
struct vrtc {scalar_t__ base_rtctime; TYPE_1__ rtcdev; } ;

/* Variables and functions */
 scalar_t__ VRTC_BROKEN_TIME ; 
 int /*<<< orphan*/  divider_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ rtc_halted (struct vrtc*) ; 

__attribute__((used)) static __inline bool
update_enabled(struct vrtc *vrtc)
{
	/*
	 * RTC date/time can be updated only if:
	 * - divider is not held in reset
	 * - guest has not disabled updates
	 * - the date/time fields have valid contents
	 */
	if (!divider_enabled(vrtc->rtcdev.reg_a))
		return (false);

	if (rtc_halted(vrtc))
		return (false);

	if (vrtc->base_rtctime == VRTC_BROKEN_TIME)
		return (false);

	return (true);
}