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
struct snd_ac97 {int dummy; } ;
typedef  int /*<<< orphan*/  iomux_v3_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_GPIO_TXFS ; 
 int /*<<< orphan*/  MX35_PAD_STXFS4__AUDMUX_AUD4_TXFS ; 
 int /*<<< orphan*/  MX35_PAD_STXFS4__GPIO2_31 ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_iomux_v3_setup_pad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pcm043_ac97_warm_reset(struct snd_ac97 *ac97)
{
	iomux_v3_cfg_t txfs_gpio = MX35_PAD_STXFS4__GPIO2_31;
	iomux_v3_cfg_t txfs = MX35_PAD_STXFS4__AUDMUX_AUD4_TXFS;
	int ret;

	ret = gpio_request(AC97_GPIO_TXFS, "SSI");
	if (ret) {
		printk("failed to get GPIO_TXFS: %d\n", ret);
		return;
	}

	mxc_iomux_v3_setup_pad(txfs_gpio);

	/* warm reset */
	gpio_direction_output(AC97_GPIO_TXFS, 1);
	udelay(2);
	gpio_set_value(AC97_GPIO_TXFS, 0);

	gpio_free(AC97_GPIO_TXFS);
	mxc_iomux_v3_setup_pad(txfs);
}