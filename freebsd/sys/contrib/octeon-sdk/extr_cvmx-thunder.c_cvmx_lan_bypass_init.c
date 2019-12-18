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
 int /*<<< orphan*/  BYPASS_EN ; 
 int /*<<< orphan*/  WDT_BP_CLR ; 
 int /*<<< orphan*/  cvmx_gpio_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_gpio_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_rtc_ds1374_alarm_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int const) ; 

__attribute__((used)) static int cvmx_lan_bypass_init(void)
{
    const int CLR_PULSE = 100;  /* Longer than 100 ns (on CPUs up to 1 GHz) */

    //Clear GPIO 6
    cvmx_gpio_clear(BYPASS_EN);

    //Disable WDT
    cvmx_rtc_ds1374_alarm_set(0);

    //GPIO(7) Send a low pulse
    cvmx_gpio_clear(WDT_BP_CLR);
    cvmx_wait(CLR_PULSE);
    cvmx_gpio_set(WDT_BP_CLR);
    return 0;
}