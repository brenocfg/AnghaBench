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
struct ena_eth_io_tx_cdesc {int dummy; } ;
struct ena_eth_io_rx_cdesc_base {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  mem_handle; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_cq {int cdesc_entry_size_in_bytes; scalar_t__ direction; size_t q_depth; int phase; scalar_t__ head; TYPE_1__ cdesc_addr; int /*<<< orphan*/  bus; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; int /*<<< orphan*/  bus; } ;
struct ena_com_create_io_ctx {int /*<<< orphan*/  numa_node; } ;

/* Variables and functions */
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_TX ; 
 int ENA_COM_NO_MEM ; 
 int /*<<< orphan*/  ENA_MEM_ALLOC_COHERENT (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_MEM_ALLOC_COHERENT_NODE (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

__attribute__((used)) static int ena_com_init_io_cq(struct ena_com_dev *ena_dev,
			      struct ena_com_create_io_ctx *ctx,
			      struct ena_com_io_cq *io_cq)
{
	size_t size;
	int prev_node = 0;

	memset(&io_cq->cdesc_addr, 0x0, sizeof(io_cq->cdesc_addr));

	/* Use the basic completion descriptor for Rx */
	io_cq->cdesc_entry_size_in_bytes =
		(io_cq->direction == ENA_COM_IO_QUEUE_DIRECTION_TX) ?
		sizeof(struct ena_eth_io_tx_cdesc) :
		sizeof(struct ena_eth_io_rx_cdesc_base);

	size = io_cq->cdesc_entry_size_in_bytes * io_cq->q_depth;
	io_cq->bus = ena_dev->bus;

	ENA_MEM_ALLOC_COHERENT_NODE(ena_dev->dmadev,
			size,
			io_cq->cdesc_addr.virt_addr,
			io_cq->cdesc_addr.phys_addr,
			io_cq->cdesc_addr.mem_handle,
			ctx->numa_node,
			prev_node);
	if (!io_cq->cdesc_addr.virt_addr) {
		ENA_MEM_ALLOC_COHERENT(ena_dev->dmadev,
				       size,
				       io_cq->cdesc_addr.virt_addr,
				       io_cq->cdesc_addr.phys_addr,
				       io_cq->cdesc_addr.mem_handle);
	}

	if (!io_cq->cdesc_addr.virt_addr) {
		ena_trc_err("memory allocation failed\n");
		return ENA_COM_NO_MEM;
	}

	io_cq->phase = 1;
	io_cq->head = 0;

	return 0;
}