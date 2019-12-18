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
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct oxnas_restart_context {TYPE_1__ restart_handler; struct regmap* sys_ctrl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct oxnas_restart_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ox820_restart_handle ; 
 int register_restart_handler (TYPE_1__*) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ox820_restart_probe(struct platform_device *pdev)
{
	struct oxnas_restart_context *ctx;
	struct regmap *sys_ctrl;
	struct device *dev = &pdev->dev;
	int err = 0;

	sys_ctrl = syscon_node_to_regmap(pdev->dev.of_node);
	if (IS_ERR(sys_ctrl))
		return PTR_ERR(sys_ctrl);

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->sys_ctrl = sys_ctrl;
	ctx->restart_handler.notifier_call = ox820_restart_handle;
	ctx->restart_handler.priority = 192;
	err = register_restart_handler(&ctx->restart_handler);
	if (err)
		dev_err(dev, "can't register restart notifier (err=%d)\n", err);

	return err;
}