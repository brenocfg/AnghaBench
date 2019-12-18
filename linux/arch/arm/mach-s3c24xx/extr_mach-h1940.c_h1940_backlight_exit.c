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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H1940_LATCH_MAX1698_nSHUTDOWN ; 
 int /*<<< orphan*/  S3C2410_GPB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void h1940_backlight_exit(struct device *dev)
{
	gpio_direction_output(S3C2410_GPB(0), 1);
	gpio_set_value(H1940_LATCH_MAX1698_nSHUTDOWN, 0);
}