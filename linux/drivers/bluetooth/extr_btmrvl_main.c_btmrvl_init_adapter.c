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
typedef  int /*<<< orphan*/  u8 ;
struct btmrvl_private {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_hs_wait_q; int /*<<< orphan*/  cmd_wait_q; int /*<<< orphan*/ * hw_regs; int /*<<< orphan*/  hw_regs_buf; int /*<<< orphan*/  ps_state; int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 scalar_t__ ALIGN_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ALIGN_SZ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTSDIO_DMA_ALIGN ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PS_AWAKE ; 
 int /*<<< orphan*/  SDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btmrvl_init_adapter(struct btmrvl_private *priv)
{
	int buf_size;

	skb_queue_head_init(&priv->adapter->tx_queue);

	priv->adapter->ps_state = PS_AWAKE;

	buf_size = ALIGN_SZ(SDIO_BLOCK_SIZE, BTSDIO_DMA_ALIGN);
	priv->adapter->hw_regs_buf = kzalloc(buf_size, GFP_KERNEL);
	if (!priv->adapter->hw_regs_buf) {
		priv->adapter->hw_regs = NULL;
		BT_ERR("Unable to allocate buffer for hw_regs.");
	} else {
		priv->adapter->hw_regs =
			(u8 *)ALIGN_ADDR(priv->adapter->hw_regs_buf,
					 BTSDIO_DMA_ALIGN);
		BT_DBG("hw_regs_buf=%p hw_regs=%p",
		       priv->adapter->hw_regs_buf, priv->adapter->hw_regs);
	}

	init_waitqueue_head(&priv->adapter->cmd_wait_q);
	init_waitqueue_head(&priv->adapter->event_hs_wait_q);
}