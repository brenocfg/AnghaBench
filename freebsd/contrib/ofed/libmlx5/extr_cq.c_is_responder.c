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
typedef  int uint8_t ;

/* Variables and functions */
#define  MLX5_CQE_RESP_ERR 132 
#define  MLX5_CQE_RESP_SEND 131 
#define  MLX5_CQE_RESP_SEND_IMM 130 
#define  MLX5_CQE_RESP_SEND_INV 129 
#define  MLX5_CQE_RESP_WR_IMM 128 

__attribute__((used)) static inline int is_responder(uint8_t opcode)
{
	switch (opcode) {
	case MLX5_CQE_RESP_WR_IMM:
	case MLX5_CQE_RESP_SEND:
	case MLX5_CQE_RESP_SEND_IMM:
	case MLX5_CQE_RESP_SEND_INV:
	case MLX5_CQE_RESP_ERR:
		return 1;
	}

	return 0;
}