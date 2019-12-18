#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct btmrvl_sdio_card {TYPE_3__* plt_wake_cfg; struct btmrvl_private* priv; } ;
struct TYPE_4__ {struct hci_dev* hcidev; } ;
struct btmrvl_private {TYPE_2__* adapter; TYPE_1__ btmrvl_dev; int /*<<< orphan*/  (* hw_wakeup_firmware ) (struct btmrvl_private*) ;} ;
typedef  int /*<<< orphan*/  mmc_pm_flag_t ;
struct TYPE_6__ {scalar_t__ irq_bt; scalar_t__ wake_by_bt; } ;
struct TYPE_5__ {int is_suspended; int /*<<< orphan*/  hs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  HS_DEACTIVATED ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  disable_irq_wake (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  hci_resume_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  sdio_func_id (struct sdio_func*) ; 
 struct btmrvl_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_get_host_pm_caps (struct sdio_func*) ; 
 int /*<<< orphan*/  stub1 (struct btmrvl_private*) ; 

__attribute__((used)) static int btmrvl_sdio_resume(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct btmrvl_sdio_card *card;
	struct btmrvl_private *priv;
	mmc_pm_flag_t pm_flags;
	struct hci_dev *hcidev;

	if (func) {
		pm_flags = sdio_get_host_pm_caps(func);
		BT_DBG("%s: resume: PM flags = 0x%x", sdio_func_id(func),
		       pm_flags);
		card = sdio_get_drvdata(func);
		if (!card || !card->priv) {
			BT_ERR("card or priv structure is not valid");
			return 0;
		}
	} else {
		BT_ERR("sdio_func is not specified");
		return 0;
	}
	priv = card->priv;

	if (!priv->adapter->is_suspended) {
		BT_DBG("device already resumed");
		return 0;
	}

	priv->hw_wakeup_firmware(priv);
	priv->adapter->hs_state = HS_DEACTIVATED;
	hcidev = priv->btmrvl_dev.hcidev;
	BT_DBG("%s: HS DEACTIVATED in resume!", hcidev->name);
	priv->adapter->is_suspended = false;
	BT_DBG("%s: SDIO resume", hcidev->name);
	hci_resume_dev(hcidev);

	/* Disable platform specific wakeup interrupt */
	if (card->plt_wake_cfg && card->plt_wake_cfg->irq_bt >= 0) {
		disable_irq_wake(card->plt_wake_cfg->irq_bt);
		disable_irq(card->plt_wake_cfg->irq_bt);
		if (card->plt_wake_cfg->wake_by_bt)
			/* Undo our disable, since interrupt handler already
			 * did this.
			 */
			enable_irq(card->plt_wake_cfg->irq_bt);
	}

	return 0;
}