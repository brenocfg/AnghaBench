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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C64XX_GPC (int) ; 
 int /*<<< orphan*/  S3C64XX_GPH (int) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgrange_nopull (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void s3c64xx_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	/* Set all the necessary GPH pins to special-function 3 */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPH(6), width, S3C_GPIO_SFN(3));

	/* Set all the necessary GPC pins to special-function 3 */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPC(4), 2, S3C_GPIO_SFN(3));
}