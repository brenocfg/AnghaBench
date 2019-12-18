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
typedef  int u32 ;
struct hifn_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_0_PUCTRL ; 
 int HIFN_PUCTRL_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hifn_read_0 (struct hifn_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hifn_wait_puc(struct hifn_device *dev)
{
	int i;
	u32 ret;

	for (i = 10000; i > 0; --i) {
		ret = hifn_read_0(dev, HIFN_0_PUCTRL);
		if (!(ret & HIFN_PUCTRL_RESET))
			break;

		udelay(1);
	}

	if (!i)
		dev_err(&dev->pdev->dev, "Failed to reset PUC unit.\n");
}