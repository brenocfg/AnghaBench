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
struct sirf_data {int /*<<< orphan*/  on_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIRF_ON_OFF_PULSE_TIME ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sirf_pulse_on_off(struct sirf_data *data)
{
	gpiod_set_value_cansleep(data->on_off, 1);
	msleep(SIRF_ON_OFF_PULSE_TIME);
	gpiod_set_value_cansleep(data->on_off, 0);
}