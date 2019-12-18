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
 int /*<<< orphan*/  cvmx_rtc_ds1374_alarm_counter_set (int) ; 

void cvmx_lan_bypass_keep_alive_ms(uint32_t interval_ms)
{
    cvmx_rtc_ds1374_alarm_counter_set((interval_ms * 0x1000) / 1000);
}