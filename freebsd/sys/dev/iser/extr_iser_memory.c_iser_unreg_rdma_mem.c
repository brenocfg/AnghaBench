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
struct iser_mem_reg {int /*<<< orphan*/ * mem_h; } ;
struct icl_iser_pdu {TYPE_1__* iser_conn; struct iser_mem_reg* rdma_reg; } ;
typedef  enum iser_data_dir { ____Placeholder_iser_data_dir } iser_data_dir ;
struct TYPE_2__ {int /*<<< orphan*/  ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  iser_reg_desc_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
iser_unreg_rdma_mem(struct icl_iser_pdu *iser_pdu,
		    enum iser_data_dir cmd_dir)
{
	struct iser_mem_reg *reg = &iser_pdu->rdma_reg[cmd_dir];

	if (!reg->mem_h)
		return;

	iser_reg_desc_put(&iser_pdu->iser_conn->ib_conn,
			  reg->mem_h);
	reg->mem_h = NULL;
}