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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hisi_crg_dev {int /*<<< orphan*/  clk_data; int /*<<< orphan*/  rstc; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* register_clks ) (struct platform_device*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct hisi_crg_dev* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_reset_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_reset_init (struct platform_device*) ; 
 TYPE_1__* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hisi_crg_dev*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 

__attribute__((used)) static int hi3516cv300_crg_probe(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg;

	crg = devm_kmalloc(&pdev->dev, sizeof(*crg), GFP_KERNEL);
	if (!crg)
		return -ENOMEM;

	crg->funcs = of_device_get_match_data(&pdev->dev);
	if (!crg->funcs)
		return -ENOENT;

	crg->rstc = hisi_reset_init(pdev);
	if (!crg->rstc)
		return -ENOMEM;

	crg->clk_data = crg->funcs->register_clks(pdev);
	if (IS_ERR(crg->clk_data)) {
		hisi_reset_exit(crg->rstc);
		return PTR_ERR(crg->clk_data);
	}

	platform_set_drvdata(pdev, crg);
	return 0;
}