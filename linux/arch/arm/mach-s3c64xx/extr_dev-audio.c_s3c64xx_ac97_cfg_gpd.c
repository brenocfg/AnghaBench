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
 int /*<<< orphan*/  S3C64XX_GPD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int s3c_gpio_cfgpin_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c64xx_ac97_cfg_gpd(struct platform_device *pdev)
{
	return s3c_gpio_cfgpin_range(S3C64XX_GPD(0), 5, S3C_GPIO_SFN(4));
}