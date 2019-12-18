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
typedef  int /*<<< orphan*/  u64 ;
struct mbuf {int /*<<< orphan*/  m_len; struct mbuf* m_next; } ;
struct ipoib_tx_buf {int /*<<< orphan*/ * mapping; struct mbuf* mb; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ipoib_dma_unmap_tx(struct ib_device *ca, struct ipoib_tx_buf *tx_req)
{
	struct mbuf *mb = tx_req->mb;
	u64 *mapping = tx_req->mapping;
	struct mbuf *m;
	int i;

	for (m = mb, i = 0; m != NULL; m = m->m_next, i++)
		ib_dma_unmap_single(ca, mapping[i], m->m_len, DMA_TO_DEVICE);
}