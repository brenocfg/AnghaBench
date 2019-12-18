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
typedef  int /*<<< orphan*/  uint32_t ;
struct ibv_send_wr {int opcode; int /*<<< orphan*/  imm_data; } ;

/* Variables and functions */
#define  IBV_WR_RDMA_WRITE_WITH_IMM 130 
#define  IBV_WR_SEND_WITH_IMM 129 
#define  IBV_WR_SEND_WITH_INV 128 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t send_ieth(struct ibv_send_wr *wr)
{
	switch (wr->opcode) {
	case IBV_WR_SEND_WITH_IMM:
	case IBV_WR_RDMA_WRITE_WITH_IMM:
		return wr->imm_data;
	case IBV_WR_SEND_WITH_INV:
		return htobe32(wr->imm_data);
	default:
		return 0;
	}
}