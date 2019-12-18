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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_RTC_DS1374_ADDR ; 
 scalar_t__ RTC_WD_ALM_CNT_BYTE0_ADDR ; 
 int cvmx_twsi_write8 (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int cvmx_rtc_ds1374_alarm_counter_set(uint32_t interval)
{
    int i;
    int rc = 0;

    for(i=0;i<3;i++)
    {
        rc |= cvmx_twsi_write8(CVMX_RTC_DS1374_ADDR, RTC_WD_ALM_CNT_BYTE0_ADDR+i, interval & 0xFF);
        interval >>= 8;
    }
    return rc;
}