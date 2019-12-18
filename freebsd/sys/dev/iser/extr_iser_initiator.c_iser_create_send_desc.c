#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct iser_tx_desc {int num_sge; TYPE_1__* tx_sg; TYPE_4__ iser_header; int /*<<< orphan*/  dma_addr; } ;
struct iser_hdr {int dummy; } ;
struct iser_device {TYPE_2__* mr; int /*<<< orphan*/  ib_device; } ;
struct TYPE_7__ {struct iser_device* device; } ;
struct iser_conn {TYPE_3__ ib_conn; } ;
struct TYPE_6__ {scalar_t__ lkey; } ;
struct TYPE_5__ {scalar_t__ lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISER_DBG (char*,struct iser_tx_desc*) ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ISER_VER ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void
iser_create_send_desc(struct iser_conn *iser_conn,
		      struct iser_tx_desc *tx_desc)
{
	struct iser_device *device = iser_conn->ib_conn.device;

	ib_dma_sync_single_for_cpu(device->ib_device,
		tx_desc->dma_addr, ISER_HEADERS_LEN, DMA_TO_DEVICE);

	memset(&tx_desc->iser_header, 0, sizeof(struct iser_hdr));
	tx_desc->iser_header.flags = ISER_VER;

	tx_desc->num_sge = 1;

	if (tx_desc->tx_sg[0].lkey != device->mr->lkey) {
		tx_desc->tx_sg[0].lkey = device->mr->lkey;
		ISER_DBG("sdesc %p lkey mismatch, fixing", tx_desc);
	}
}