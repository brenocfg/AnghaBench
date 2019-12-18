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
struct TYPE_6__ {int /*<<< orphan*/ * base_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  mem_handle; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_sq {size_t desc_entry_size; size_t q_depth; TYPE_3__ bounce_buf_ctrl; TYPE_2__ desc_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  mem_handle; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_cq {size_t cdesc_entry_size_in_bytes; size_t q_depth; TYPE_1__ cdesc_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_MEM_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENA_MEM_FREE_COHERENT (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_com_io_queue_free(struct ena_com_dev *ena_dev,
				  struct ena_com_io_sq *io_sq,
				  struct ena_com_io_cq *io_cq)
{
	size_t size;

	if (io_cq->cdesc_addr.virt_addr) {
		size = io_cq->cdesc_entry_size_in_bytes * io_cq->q_depth;

		ENA_MEM_FREE_COHERENT(ena_dev->dmadev,
				      size,
				      io_cq->cdesc_addr.virt_addr,
				      io_cq->cdesc_addr.phys_addr,
				      io_cq->cdesc_addr.mem_handle);

		io_cq->cdesc_addr.virt_addr = NULL;
	}

	if (io_sq->desc_addr.virt_addr) {
		size = io_sq->desc_entry_size * io_sq->q_depth;

		ENA_MEM_FREE_COHERENT(ena_dev->dmadev,
				      size,
				      io_sq->desc_addr.virt_addr,
				      io_sq->desc_addr.phys_addr,
				      io_sq->desc_addr.mem_handle);

		io_sq->desc_addr.virt_addr = NULL;
	}

	if (io_sq->bounce_buf_ctrl.base_buffer) {
		ENA_MEM_FREE(ena_dev->dmadev, io_sq->bounce_buf_ctrl.base_buffer);
		io_sq->bounce_buf_ctrl.base_buffer = NULL;
	}
}