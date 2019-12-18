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
struct sk_buff {int dummy; } ;
struct fe_tx_buf {struct sk_buff* skb; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_DUMMY_DESC ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_addr0 ; 
 int /*<<< orphan*/  dma_addr1 ; 
 int /*<<< orphan*/  dma_len0 ; 
 int /*<<< orphan*/  dma_len1 ; 
 int /*<<< orphan*/  dma_unmap_addr (struct fe_tx_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct fe_tx_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct fe_tx_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fe_txd_unmap(struct device *dev, struct fe_tx_buf *tx_buf)
{
	if (dma_unmap_len(tx_buf, dma_len0))
		dma_unmap_page(dev,
			       dma_unmap_addr(tx_buf, dma_addr0),
			       dma_unmap_len(tx_buf, dma_len0),
			       DMA_TO_DEVICE);

	if (dma_unmap_len(tx_buf, dma_len1))
		dma_unmap_page(dev,
			       dma_unmap_addr(tx_buf, dma_addr1),
			       dma_unmap_len(tx_buf, dma_len1),
			       DMA_TO_DEVICE);

	dma_unmap_len_set(tx_buf, dma_addr0, 0);
	dma_unmap_len_set(tx_buf, dma_addr1, 0);
	if (tx_buf->skb && (tx_buf->skb != (struct sk_buff *)DMA_DUMMY_DESC))
		dev_kfree_skb_any(tx_buf->skb);
	tx_buf->skb = NULL;
}