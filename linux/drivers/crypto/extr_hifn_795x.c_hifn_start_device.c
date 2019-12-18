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
struct hifn_device {scalar_t__ active; scalar_t__ started; } ;

/* Variables and functions */
 int hifn_enable_crypto (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_init_dma (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_init_pubrng (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_init_registers (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_reset_dma (struct hifn_device*,int) ; 
 int /*<<< orphan*/  hifn_reset_puc (struct hifn_device*) ; 

__attribute__((used)) static int hifn_start_device(struct hifn_device *dev)
{
	int err;

	dev->started = dev->active = 0;
	hifn_reset_dma(dev, 1);

	err = hifn_enable_crypto(dev);
	if (err)
		return err;

	hifn_reset_puc(dev);

	hifn_init_dma(dev);

	hifn_init_registers(dev);

	hifn_init_pubrng(dev);

	return 0;
}