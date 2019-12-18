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
struct mlx4_cqe {int owner_sr_opcode; int /*<<< orphan*/  byte_cnt; } ;
struct ibv_wc {int byte_len; void* opcode; scalar_t__ wc_flags; } ;

/* Variables and functions */
 void* IBV_WC_BIND_MW ; 
 void* IBV_WC_COMP_SWAP ; 
 void* IBV_WC_FETCH_ADD ; 
 void* IBV_WC_LOCAL_INV ; 
 void* IBV_WC_RDMA_READ ; 
 void* IBV_WC_RDMA_WRITE ; 
 void* IBV_WC_SEND ; 
 scalar_t__ IBV_WC_WITH_IMM ; 
 int MLX4_CQE_OPCODE_MASK ; 
#define  MLX4_OPCODE_ATOMIC_CS 137 
#define  MLX4_OPCODE_ATOMIC_FA 136 
#define  MLX4_OPCODE_BIND_MW 135 
#define  MLX4_OPCODE_LOCAL_INVAL 134 
#define  MLX4_OPCODE_RDMA_READ 133 
#define  MLX4_OPCODE_RDMA_WRITE 132 
#define  MLX4_OPCODE_RDMA_WRITE_IMM 131 
#define  MLX4_OPCODE_SEND 130 
#define  MLX4_OPCODE_SEND_IMM 129 
#define  MLX4_OPCODE_SEND_INVAL 128 
 int /*<<< orphan*/  SWITCH_FALLTHROUGH ; 
 int be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void handle_good_req(struct ibv_wc *wc, struct mlx4_cqe *cqe)
{
	wc->wc_flags = 0;
	switch (cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) {
	case MLX4_OPCODE_RDMA_WRITE_IMM:
		wc->wc_flags |= IBV_WC_WITH_IMM;
		SWITCH_FALLTHROUGH;
	case MLX4_OPCODE_RDMA_WRITE:
		wc->opcode    = IBV_WC_RDMA_WRITE;
		break;
	case MLX4_OPCODE_SEND_IMM:
		wc->wc_flags |= IBV_WC_WITH_IMM;
		SWITCH_FALLTHROUGH;
	case MLX4_OPCODE_SEND:
	case MLX4_OPCODE_SEND_INVAL:
		wc->opcode    = IBV_WC_SEND;
		break;
	case MLX4_OPCODE_RDMA_READ:
		wc->opcode    = IBV_WC_RDMA_READ;
		wc->byte_len  = be32toh(cqe->byte_cnt);
		break;
	case MLX4_OPCODE_ATOMIC_CS:
		wc->opcode    = IBV_WC_COMP_SWAP;
		wc->byte_len  = 8;
		break;
	case MLX4_OPCODE_ATOMIC_FA:
		wc->opcode    = IBV_WC_FETCH_ADD;
		wc->byte_len  = 8;
		break;
	case MLX4_OPCODE_LOCAL_INVAL:
		wc->opcode    = IBV_WC_LOCAL_INV;
		break;
	case MLX4_OPCODE_BIND_MW:
		wc->opcode    = IBV_WC_BIND_MW;
		break;
	default:
		/* assume it's a send completion */
		wc->opcode    = IBV_WC_SEND;
		break;
	}
}