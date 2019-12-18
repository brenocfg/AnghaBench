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
struct mv_rtc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RTC_ALARM_1 ; 
 int /*<<< orphan*/  RTC_ALARM_2 ; 
 int /*<<< orphan*/  RTC_CLOCK_CORR ; 
 int /*<<< orphan*/  RTC_IRQ_1_CONFIG ; 
 int /*<<< orphan*/  RTC_IRQ_2_CONFIG ; 
 int RTC_NOMINAL_TIMING ; 
 int /*<<< orphan*/  RTC_STATUS ; 
 int RTC_STATUS_ALARM1_MASK ; 
 int RTC_STATUS_ALARM2_MASK ; 
 int /*<<< orphan*/  RTC_TEST_CONFIG ; 
 int /*<<< orphan*/  RTC_TIME ; 
 struct mv_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_rtc_reg_write (struct mv_rtc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mv_rtc_reset(device_t dev)
{
	struct mv_rtc_softc *sc;

	sc = device_get_softc(dev);

	/* Reset Test register */
	mv_rtc_reg_write(sc, RTC_TEST_CONFIG, 0);
	DELAY(500000);

	/* Reset Time register */
	mv_rtc_reg_write(sc, RTC_TIME, 0);
	DELAY(62);

	/* Reset Status register */
	mv_rtc_reg_write(sc, RTC_STATUS, (RTC_STATUS_ALARM1_MASK | RTC_STATUS_ALARM2_MASK));
	DELAY(62);

	/* Turn off Int1 and Int2 sources & clear the Alarm count */
	mv_rtc_reg_write(sc, RTC_IRQ_1_CONFIG, 0);
	mv_rtc_reg_write(sc, RTC_IRQ_2_CONFIG, 0);
	mv_rtc_reg_write(sc, RTC_ALARM_1, 0);
	mv_rtc_reg_write(sc, RTC_ALARM_2, 0);

	/* Setup nominal register access timing */
	mv_rtc_reg_write(sc, RTC_CLOCK_CORR, RTC_NOMINAL_TIMING);

	/* Reset Time register */
	mv_rtc_reg_write(sc, RTC_TIME, 0);
	DELAY(10);

	/* Reset Status register */
	mv_rtc_reg_write(sc, RTC_STATUS, (RTC_STATUS_ALARM1_MASK | RTC_STATUS_ALARM2_MASK));
	DELAY(50);
}