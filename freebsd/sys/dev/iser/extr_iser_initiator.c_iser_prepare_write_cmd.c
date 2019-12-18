#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct iser_mem_reg {TYPE_1__ sge; int /*<<< orphan*/  rkey; } ;
struct iser_hdr {int /*<<< orphan*/  write_va; int /*<<< orphan*/  write_stag; int /*<<< orphan*/  flags; } ;
struct iser_data_buf {int dummy; } ;
struct TYPE_4__ {struct iser_hdr iser_header; } ;
struct icl_iser_pdu {struct iser_mem_reg* rdma_reg; struct iser_data_buf* data; TYPE_2__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  ISER_ERR (char*) ; 
 int /*<<< orphan*/  ISER_WSV ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int iser_dma_map_task_data (struct icl_iser_pdu*,struct iser_data_buf*,size_t,int /*<<< orphan*/ ) ; 
 int iser_reg_rdma_mem (struct icl_iser_pdu*,size_t) ; 

__attribute__((used)) static int
iser_prepare_write_cmd(struct icl_iser_pdu *iser_pdu)
{
	struct iser_hdr *hdr = &iser_pdu->desc.iser_header;
	struct iser_data_buf *buf_out = &iser_pdu->data[ISER_DIR_OUT];
	struct iser_mem_reg *mem_reg;
	int err;

	err = iser_dma_map_task_data(iser_pdu,
				     buf_out,
				     ISER_DIR_OUT,
				     DMA_TO_DEVICE);
	if (err)
		return (err);

	err = iser_reg_rdma_mem(iser_pdu, ISER_DIR_OUT);
	if (err) {
		ISER_ERR("Failed to set up Data-out RDMA");
		return (err);
	}

	mem_reg = &iser_pdu->rdma_reg[ISER_DIR_OUT];

	hdr->flags     |= ISER_WSV;
	hdr->write_stag = cpu_to_be32(mem_reg->rkey);
	hdr->write_va   = cpu_to_be64(mem_reg->sge.addr);

	return (0);
}