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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_cmd_prot_block {scalar_t__ next; } ;
struct mlx5_cmd_msg {size_t numpages; } ;

/* Variables and functions */
 size_t MLX5_CMD_MBOX_SIZE ; 
 size_t MLX5_NUM_CMDS_IN_ADAPTER_PAGE ; 
 int /*<<< orphan*/  calc_block_sig (struct mlx5_cmd_prot_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fwp_flush (struct mlx5_cmd_msg*) ; 
 struct mlx5_cmd_prot_block* mlx5_fwp_get_virt (struct mlx5_cmd_msg*,size_t) ; 

__attribute__((used)) static void
calc_chain_sig(struct mlx5_cmd_msg *msg, u8 token, int csum)
{
	size_t i;

	for (i = 0; i != (msg->numpages * MLX5_NUM_CMDS_IN_ADAPTER_PAGE); i++) {
		struct mlx5_cmd_prot_block *block;

		block = mlx5_fwp_get_virt(msg, i * MLX5_CMD_MBOX_SIZE);

		/* compute signature */
		calc_block_sig(block, token, csum);

		/* check for last block */
		if (block->next == 0)
			break;
	}

	/* make sure data gets written to RAM */
	mlx5_fwp_flush(msg);
}