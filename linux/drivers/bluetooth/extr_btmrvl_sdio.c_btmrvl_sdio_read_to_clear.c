#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct btmrvl_sdio_card {TYPE_1__* reg; int /*<<< orphan*/  func; TYPE_2__* priv; } ;
struct btmrvl_adapter {int /*<<< orphan*/ * hw_regs; } ;
struct TYPE_4__ {struct btmrvl_adapter* adapter; } ;
struct TYPE_3__ {size_t host_intstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int /*<<< orphan*/  SDIO_BLOCK_SIZE ; 
 int sdio_readsb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmrvl_sdio_read_to_clear(struct btmrvl_sdio_card *card, u8 *ireg)
{
	struct btmrvl_adapter *adapter = card->priv->adapter;
	int ret;

	ret = sdio_readsb(card->func, adapter->hw_regs, 0, SDIO_BLOCK_SIZE);
	if (ret) {
		BT_ERR("sdio_readsb: read int hw_regs failed: %d", ret);
		return ret;
	}

	*ireg = adapter->hw_regs[card->reg->host_intstatus];
	BT_DBG("hw_regs[%#x]=%#x", card->reg->host_intstatus, *ireg);

	return 0;
}