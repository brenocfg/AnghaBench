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
 int /*<<< orphan*/  RTCSB_PINTR ; 
 int /*<<< orphan*/  RTC_INTR ; 
 int /*<<< orphan*/  RTC_STATUSB ; 
 int /*<<< orphan*/  atrtc_lock ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_statusb ; 
 int /*<<< orphan*/  rtcin_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcout_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atrtc_enable_intr(void)
{

	rtc_statusb |= RTCSB_PINTR;
	mtx_lock_spin(&atrtc_lock);
	rtcout_locked(RTC_STATUSB, rtc_statusb);
	rtcin_locked(RTC_INTR);
	mtx_unlock_spin(&atrtc_lock);
}