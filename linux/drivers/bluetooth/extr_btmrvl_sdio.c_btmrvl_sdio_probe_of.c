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
struct device {scalar_t__ of_node; } ;
struct btmrvl_sdio_card {scalar_t__ plt_of_node; struct btmrvl_plt_wake_cfg* plt_wake_cfg; } ;
struct btmrvl_plt_wake_cfg {int irq_bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  btmrvl_sdio_of_match_table ; 
 int /*<<< orphan*/  btmrvl_wake_irq_bt ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct btmrvl_plt_wake_cfg* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct btmrvl_sdio_card*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int irq_of_parse_and_map (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int btmrvl_sdio_probe_of(struct device *dev,
				struct btmrvl_sdio_card *card)
{
	struct btmrvl_plt_wake_cfg *cfg;
	int ret;

	if (!dev->of_node ||
	    !of_match_node(btmrvl_sdio_of_match_table, dev->of_node)) {
		dev_info(dev, "sdio device tree data not available\n");
		return -1;
	}

	card->plt_of_node = dev->of_node;

	card->plt_wake_cfg = devm_kzalloc(dev, sizeof(*card->plt_wake_cfg),
					  GFP_KERNEL);
	cfg = card->plt_wake_cfg;
	if (cfg && card->plt_of_node) {
		cfg->irq_bt = irq_of_parse_and_map(card->plt_of_node, 0);
		if (!cfg->irq_bt) {
			dev_err(dev, "fail to parse irq_bt from device tree\n");
			cfg->irq_bt = -1;
		} else {
			ret = devm_request_irq(dev, cfg->irq_bt,
					       btmrvl_wake_irq_bt,
					       0, "bt_wake", card);
			if (ret) {
				dev_err(dev,
					"Failed to request irq_bt %d (%d)\n",
					cfg->irq_bt, ret);
			}
			disable_irq(cfg->irq_bt);
		}
	}

	return 0;
}