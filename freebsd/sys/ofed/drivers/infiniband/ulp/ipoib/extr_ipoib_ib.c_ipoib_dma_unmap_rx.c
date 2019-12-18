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
struct mbuf {int /*<<< orphan*/  m_len; struct mbuf* m_next; } ;
struct ipoib_rx_buf {int /*<<< orphan*/ * mapping; struct mbuf* mb; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipoib_dma_unmap_rx(struct ipoib_dev_priv *priv, struct ipoib_rx_buf *rx_req)
{
	struct mbuf *m;
	int i;

	for (i = 0, m = rx_req->mb; m != NULL; m = m->m_next, i++)
		ib_dma_unmap_single(priv->ca, rx_req->mapping[i], m->m_len,
		    DMA_FROM_DEVICE);
}