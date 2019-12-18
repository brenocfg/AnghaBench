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
typedef  int /*<<< orphan*/  u64 ;
struct iser_tx_desc {int mapped; TYPE_2__* tx_sg; int /*<<< orphan*/  dma_addr; } ;
struct iser_device {TYPE_3__* mr; int /*<<< orphan*/  ib_device; } ;
struct TYPE_4__ {struct iser_device* device; } ;
struct iser_conn {TYPE_1__ ib_conn; } ;
struct icl_iser_pdu {struct iser_tx_desc desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
iser_initialize_headers(struct icl_iser_pdu *pdu, struct iser_conn *iser_conn)
{
	struct iser_tx_desc *tx_desc = &pdu->desc;
	struct iser_device *device = iser_conn->ib_conn.device;
	u64 dma_addr;
	int ret = 0;

	dma_addr = ib_dma_map_single(device->ib_device, (void *)tx_desc,
				ISER_HEADERS_LEN, DMA_TO_DEVICE);
	if (ib_dma_mapping_error(device->ib_device, dma_addr)) {
		ret = -ENOMEM;
		goto out;
	}

	tx_desc->mapped = true;
	tx_desc->dma_addr = dma_addr;
	tx_desc->tx_sg[0].addr   = tx_desc->dma_addr;
	tx_desc->tx_sg[0].length = ISER_HEADERS_LEN;
	tx_desc->tx_sg[0].lkey   = device->mr->lkey;

out:

	return (ret);
}