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
struct device {int dummy; } ;
struct btmrvl_sdio_card {struct btmrvl_plt_wake_cfg* plt_wake_cfg; TYPE_1__* func; } ;
struct btmrvl_plt_wake_cfg {int wake_by_bt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  pm_system_wakeup () ; 
 int /*<<< orphan*/  pm_wakeup_event (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t btmrvl_wake_irq_bt(int irq, void *priv)
{
	struct btmrvl_sdio_card *card = priv;
	struct device *dev = &card->func->dev;
	struct btmrvl_plt_wake_cfg *cfg = card->plt_wake_cfg;

	dev_info(dev, "wake by bt\n");
	cfg->wake_by_bt = true;
	disable_irq_nosync(irq);

	pm_wakeup_event(dev, 0);
	pm_system_wakeup();

	return IRQ_HANDLED;
}