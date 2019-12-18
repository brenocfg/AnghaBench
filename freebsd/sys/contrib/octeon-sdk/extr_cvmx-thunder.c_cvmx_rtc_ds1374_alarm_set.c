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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_RTC_DS1374_ADDR ; 
 int /*<<< orphan*/  RTC_CTL_ADDR ; 
 int RTC_CTL_BIT_WACE ; 
 int cvmx_twsi_read8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_twsi_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cvmx_rtc_ds1374_alarm_set(int alarm_on)
{
    uint8_t val;

    if (alarm_on)
    {
        val = cvmx_twsi_read8(CVMX_RTC_DS1374_ADDR,RTC_CTL_ADDR);
        cvmx_twsi_write8(CVMX_RTC_DS1374_ADDR,RTC_CTL_ADDR, val | RTC_CTL_BIT_WACE);
    }
    else
    {
        val = cvmx_twsi_read8(CVMX_RTC_DS1374_ADDR,RTC_CTL_ADDR);
        cvmx_twsi_write8(CVMX_RTC_DS1374_ADDR,RTC_CTL_ADDR, val & ~RTC_CTL_BIT_WACE);
    }
    return 0;
}