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
struct plat_lcd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C64XX_GPM (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void smartq_lcd_power_set(struct plat_lcd_data *pd, unsigned int power)
{
	gpio_direction_output(S3C64XX_GPM(3), power);
}