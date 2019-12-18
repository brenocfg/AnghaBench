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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u8 ;
struct btmrvl_sdio_card {int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int tx_dnld_rdy; struct btmrvl_sdio_card* card; } ;
struct btmrvl_private {TYPE_1__ btmrvl_dev; int /*<<< orphan*/  driver_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int DN_LD_HOST_INT_STATUS ; 
 int UP_LD_HOST_INT_STATUS ; 
 int /*<<< orphan*/  btmrvl_sdio_card_to_host (struct btmrvl_private*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int sdio_ireg ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmrvl_sdio_process_int_status(struct btmrvl_private *priv)
{
	ulong flags;
	u8 ireg;
	struct btmrvl_sdio_card *card = priv->btmrvl_dev.card;

	spin_lock_irqsave(&priv->driver_lock, flags);
	ireg = sdio_ireg;
	sdio_ireg = 0;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	sdio_claim_host(card->func);
	if (ireg & DN_LD_HOST_INT_STATUS) {
		if (priv->btmrvl_dev.tx_dnld_rdy)
			BT_DBG("tx_done already received: "
				" int_status=0x%x", ireg);
		else
			priv->btmrvl_dev.tx_dnld_rdy = true;
	}

	if (ireg & UP_LD_HOST_INT_STATUS)
		btmrvl_sdio_card_to_host(priv);

	sdio_release_host(card->func);

	return 0;
}