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
struct iser_rx_desc {int /*<<< orphan*/  dma_addr; } ;
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct ib_conn {struct iser_device* device; } ;
struct iser_conn {int qp_max_recv_dtos; struct iser_rx_desc* rx_descs; struct ib_conn ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ISER_RX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  M_ISER_INITIATOR ; 
 int /*<<< orphan*/  free (struct iser_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_free_fastreg_pool (struct ib_conn*) ; 

void
iser_free_rx_descriptors(struct iser_conn *iser_conn)
{
	int i;
	struct iser_rx_desc *rx_desc;
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	struct iser_device *device = ib_conn->device;

	iser_free_fastreg_pool(ib_conn);

	rx_desc = iser_conn->rx_descs;
	for (i = 0; i < iser_conn->qp_max_recv_dtos; i++, rx_desc++)
		ib_dma_unmap_single(device->ib_device, rx_desc->dma_addr,
				    ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);

	free(iser_conn->rx_descs, M_ISER_INITIATOR);

	/* make sure we never redo any unmapping */
	iser_conn->rx_descs = NULL;
}