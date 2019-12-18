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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ena_eth_io_rx_desc {int ctrl; int buff_addr_hi; scalar_t__ buff_addr_lo; int /*<<< orphan*/  req_id; int /*<<< orphan*/  length; } ;
struct ena_com_io_sq {scalar_t__ direction; int phase; scalar_t__ dma_addr_bits; } ;
struct ena_com_buf {int paddr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ENA_COM_FAULT ; 
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_RX ; 
 int ENA_COM_NO_SPACE ; 
 int ENA_ETH_IO_RX_DESC_COMP_REQ_MASK ; 
 int ENA_ETH_IO_RX_DESC_FIRST_MASK ; 
 int ENA_ETH_IO_RX_DESC_LAST_MASK ; 
 int ENA_ETH_IO_RX_DESC_PHASE_MASK ; 
 int /*<<< orphan*/  ENA_WARN (int,char*) ; 
 int GENMASK_ULL (scalar_t__,int) ; 
 int /*<<< orphan*/  ena_com_sq_have_enough_space (struct ena_com_io_sq*,int) ; 
 int ena_com_sq_update_tail (struct ena_com_io_sq*) ; 
 struct ena_eth_io_rx_desc* get_sq_desc (struct ena_com_io_sq*) ; 
 int /*<<< orphan*/  memset (struct ena_eth_io_rx_desc*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_add_single_rx_desc(struct ena_com_io_sq *io_sq,
			       struct ena_com_buf *ena_buf,
			       u16 req_id)
{
	struct ena_eth_io_rx_desc *desc;

	ENA_WARN(io_sq->direction != ENA_COM_IO_QUEUE_DIRECTION_RX,
		 "wrong Q type");

	if (unlikely(!ena_com_sq_have_enough_space(io_sq, 1)))
		return ENA_COM_NO_SPACE;

	desc = get_sq_desc(io_sq);
	if (unlikely(!desc))
		return ENA_COM_FAULT;

	memset(desc, 0x0, sizeof(struct ena_eth_io_rx_desc));

	desc->length = ena_buf->len;

	desc->ctrl = ENA_ETH_IO_RX_DESC_FIRST_MASK |
		ENA_ETH_IO_RX_DESC_LAST_MASK |
		(io_sq->phase & ENA_ETH_IO_RX_DESC_PHASE_MASK) |
		ENA_ETH_IO_RX_DESC_COMP_REQ_MASK;

	desc->req_id = req_id;

	desc->buff_addr_lo = (u32)ena_buf->paddr;
	desc->buff_addr_hi =
		((ena_buf->paddr & GENMASK_ULL(io_sq->dma_addr_bits - 1, 32)) >> 32);

	return ena_com_sq_update_tail(io_sq);
}