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
 int /*<<< orphan*/  cvmx_gpio_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_lan_bypass_init () ; 

int cvmx_lan_bypass_force(int force_bypass)
{
    if (force_bypass)
    {
        //Set GPIO 6
        cvmx_gpio_set(BYPASS_EN);
    }
    else
    {
        cvmx_lan_bypass_init();
    }
    return 0;
}