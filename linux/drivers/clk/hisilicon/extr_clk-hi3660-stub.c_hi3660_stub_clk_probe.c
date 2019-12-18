#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  hw; } ;
struct TYPE_6__ {int tx_block; int knows_txdone; int /*<<< orphan*/ * tx_done; struct device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbox; TYPE_2__ cl; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int HI3660_CLK_STUB_NUM ; 
 scalar_t__ HI3660_STUB_CLOCK_DATA ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ freq_reg ; 
 int /*<<< orphan*/  hi3660_stub_clk_hw_get ; 
 TYPE_3__* hi3660_stub_clks ; 
 int /*<<< orphan*/  mbox_request_channel (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 TYPE_1__ stub_clk_chan ; 

__attribute__((used)) static int hi3660_stub_clk_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	unsigned int i;
	int ret;

	/* Use mailbox client without blocking */
	stub_clk_chan.cl.dev = dev;
	stub_clk_chan.cl.tx_done = NULL;
	stub_clk_chan.cl.tx_block = false;
	stub_clk_chan.cl.knows_txdone = false;

	/* Allocate mailbox channel */
	stub_clk_chan.mbox = mbox_request_channel(&stub_clk_chan.cl, 0);
	if (IS_ERR(stub_clk_chan.mbox))
		return PTR_ERR(stub_clk_chan.mbox);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;
	freq_reg = devm_ioremap(dev, res->start, resource_size(res));
	if (!freq_reg)
		return -ENOMEM;

	freq_reg += HI3660_STUB_CLOCK_DATA;

	for (i = 0; i < HI3660_CLK_STUB_NUM; i++) {
		ret = devm_clk_hw_register(&pdev->dev, &hi3660_stub_clks[i].hw);
		if (ret)
			return ret;
	}

	return devm_of_clk_add_hw_provider(&pdev->dev, hi3660_stub_clk_hw_get,
					   hi3660_stub_clks);
}