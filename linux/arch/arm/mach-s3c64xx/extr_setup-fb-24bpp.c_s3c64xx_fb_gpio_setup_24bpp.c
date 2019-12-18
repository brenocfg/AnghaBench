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
 int /*<<< orphan*/  S3C64XX_GPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C64XX_GPJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgrange_nopull (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void s3c64xx_fb_gpio_setup_24bpp(void)
{
	s3c_gpio_cfgrange_nopull(S3C64XX_GPI(0), 16, S3C_GPIO_SFN(2));
	s3c_gpio_cfgrange_nopull(S3C64XX_GPJ(0), 12, S3C_GPIO_SFN(2));
}