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
struct xgbe_ring_data {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; scalar_t__ mbuf_len; scalar_t__ mbuf_data_paddr; scalar_t__ mbuf_hdr_paddr; scalar_t__ mbuf_free; int /*<<< orphan*/ * mb; int /*<<< orphan*/ * mbuf_map; int /*<<< orphan*/  mbuf_dmat; } ;
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_unmap_rdata(struct xgbe_prv_data *pdata,
			     struct xgbe_ring_data *rdata)
{

	if (rdata->mbuf_map != NULL)
		bus_dmamap_destroy(rdata->mbuf_dmat, rdata->mbuf_map);

	if (rdata->mbuf_free)
		m_freem(rdata->mb);

	rdata->mb = NULL;
	rdata->mbuf_free = 0;
	rdata->mbuf_hdr_paddr = 0;
	rdata->mbuf_data_paddr = 0;
	rdata->mbuf_len = 0;

	memset(&rdata->tx, 0, sizeof(rdata->tx));
	memset(&rdata->rx, 0, sizeof(rdata->rx));
}