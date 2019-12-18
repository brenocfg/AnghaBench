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
typedef  int /*<<< orphan*/  u8 ;
struct dbg_attn_reg {int dummy; } ;
struct dbg_attn_block_type_data {size_t regs_offset; int /*<<< orphan*/  num_regs; } ;
typedef  enum dbg_attn_type { ____Placeholder_dbg_attn_type } dbg_attn_type ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;
struct TYPE_2__ {scalar_t__ ptr; } ;

/* Variables and functions */
 size_t BIN_BUF_DBG_ATTN_REGS ; 
 struct dbg_attn_block_type_data* ecore_get_block_attn_data (int,int) ; 
 TYPE_1__* s_dbg_arrays ; 

__attribute__((used)) static const struct dbg_attn_reg* ecore_get_block_attn_regs(enum block_id block_id,
															enum dbg_attn_type attn_type,
															u8 *num_attn_regs)
{
	const struct dbg_attn_block_type_data *block_type_data = ecore_get_block_attn_data(block_id, attn_type);

	*num_attn_regs = block_type_data->num_regs;

	return &((const struct dbg_attn_reg *)s_dbg_arrays[BIN_BUF_DBG_ATTN_REGS].ptr)[block_type_data->regs_offset];
}