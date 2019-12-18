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
 int /*<<< orphan*/  S3C64XX_GPK (int) ; 
 int /*<<< orphan*/  S3C64XX_GPL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgrange_nopull (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

void samsung_keypad_cfg_gpio(unsigned int rows, unsigned int cols)
{
	/* Set all the necessary GPK pins to special-function 3: KP_ROW[x] */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPK(8), rows, S3C_GPIO_SFN(3));

	/* Set all the necessary GPL pins to special-function 3: KP_COL[x] */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPL(0), cols, S3C_GPIO_SFN(3));
}