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
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct timespec {int dummy; } ;
struct tegra_rtc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct tegra_rtc_softc*) ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  UNLOCK (struct tegra_rtc_softc*) ; 
 int /*<<< orphan*/  WR4 (struct tegra_rtc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_rtc_wait (struct tegra_rtc_softc*) ; 

__attribute__((used)) static int
tegra_rtc_settime(device_t dev, struct timespec *ts)
{
	struct tegra_rtc_softc *sc;
	struct timeval tv;

	sc = device_get_softc(dev);

	LOCK(sc);
	TIMESPEC_TO_TIMEVAL(&tv, ts);
	tegra_rtc_wait(sc);
	WR4(sc, RTC_SECONDS, tv.tv_sec);
	UNLOCK(sc);

	return (0);
}