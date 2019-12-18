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
struct iser_tx_desc {int /*<<< orphan*/  num_sge; int /*<<< orphan*/  tx_sg; int /*<<< orphan*/  dma_addr; } ;
struct ib_send_wr {uintptr_t wr_id; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  sg_list; int /*<<< orphan*/ * next; } ;
struct ib_conn {int /*<<< orphan*/  qp; TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  ISER_ERR (char*,int) ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,struct ib_send_wr**) ; 

int iser_post_send(struct ib_conn *ib_conn, struct iser_tx_desc *tx_desc,
		   bool signal)
{
	int		  ib_ret;
	struct ib_send_wr send_wr, *send_wr_failed;

	ib_dma_sync_single_for_device(ib_conn->device->ib_device,
				      tx_desc->dma_addr, ISER_HEADERS_LEN,
				      DMA_TO_DEVICE);

	send_wr.next	   = NULL;
	send_wr.wr_id	   = (uintptr_t)tx_desc;
	send_wr.sg_list	   = tx_desc->tx_sg;
	send_wr.num_sge	   = tx_desc->num_sge;
	send_wr.opcode	   = IB_WR_SEND;
	send_wr.send_flags = signal ? IB_SEND_SIGNALED : 0;

	ib_ret = ib_post_send(ib_conn->qp, &send_wr, &send_wr_failed);
	if (ib_ret)
		ISER_ERR("ib_post_send failed, ret:%d", ib_ret);

	return (ib_ret);
}