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
 int /*<<< orphan*/  RTCSB_24HR ; 
 int /*<<< orphan*/  RTC_STATUSA ; 
 int /*<<< orphan*/  RTC_STATUSB ; 
 int /*<<< orphan*/  atrtc_lock ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_statusa ; 
 int /*<<< orphan*/  rtcout_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atrtc_start(void)
{

	mtx_lock_spin(&atrtc_lock);
	rtcout_locked(RTC_STATUSA, rtc_statusa);
	rtcout_locked(RTC_STATUSB, RTCSB_24HR);
	mtx_unlock_spin(&atrtc_lock);
}