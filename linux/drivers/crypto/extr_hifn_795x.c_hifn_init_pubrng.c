#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hifn_device {int dmareg; int /*<<< orphan*/  rngtime; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_1_DMA_IER ; 
 int /*<<< orphan*/  HIFN_1_PUB_IEN ; 
 int /*<<< orphan*/  HIFN_1_PUB_RESET ; 
 int /*<<< orphan*/  HIFN_1_RNG_CONFIG ; 
 int /*<<< orphan*/  HIFN_1_RNG_DATA ; 
 int HIFN_DMAIER_PUBDONE ; 
 int HIFN_PUBIEN_DONE ; 
 int HIFN_PUBRST_RESET ; 
 int HIFN_RNGCFG_ENA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hifn_read_1 (struct hifn_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hifn_write_1 (struct hifn_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int hifn_init_pubrng(struct hifn_device *dev)
{
	int i;

	hifn_write_1(dev, HIFN_1_PUB_RESET, hifn_read_1(dev, HIFN_1_PUB_RESET) |
			HIFN_PUBRST_RESET);

	for (i = 100; i > 0; --i) {
		mdelay(1);

		if ((hifn_read_1(dev, HIFN_1_PUB_RESET) & HIFN_PUBRST_RESET) == 0)
			break;
	}

	if (!i) {
		dev_err(&dev->pdev->dev, "Failed to initialise public key engine.\n");
	} else {
		hifn_write_1(dev, HIFN_1_PUB_IEN, HIFN_PUBIEN_DONE);
		dev->dmareg |= HIFN_DMAIER_PUBDONE;
		hifn_write_1(dev, HIFN_1_DMA_IER, dev->dmareg);

		dev_dbg(&dev->pdev->dev, "Public key engine has been successfully initialised.\n");
	}

	/* Enable RNG engine. */

	hifn_write_1(dev, HIFN_1_RNG_CONFIG,
			hifn_read_1(dev, HIFN_1_RNG_CONFIG) | HIFN_RNGCFG_ENA);
	dev_dbg(&dev->pdev->dev, "RNG engine has been successfully initialised.\n");

#ifdef CONFIG_CRYPTO_DEV_HIFN_795X_RNG
	/* First value must be discarded */
	hifn_read_1(dev, HIFN_1_RNG_DATA);
	dev->rngtime = ktime_get();
#endif
	return 0;
}