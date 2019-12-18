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
 int /*<<< orphan*/  SD1_EN_GPIO ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mx27_3ds_sdhc1_enable_level_translator(void)
{
	/* Turn on TXB0108 OE pin */
	gpio_request(SD1_EN_GPIO, "sd1_enable");
	gpio_direction_output(SD1_EN_GPIO, 1);
}