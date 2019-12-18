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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dbg_tools_data {int /*<<< orphan*/ * mode_enable; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct TYPE_2__ {scalar_t__ ptr; } ;

/* Variables and functions */
 size_t BIN_BUF_DBG_MODE_TREE ; 
#define  INIT_MODE_OP_AND 130 
#define  INIT_MODE_OP_NOT 129 
#define  INIT_MODE_OP_OR 128 
 int /*<<< orphan*/  MAX_INIT_MODE_OPS ; 
 TYPE_1__* s_dbg_arrays ; 

__attribute__((used)) static bool ecore_is_mode_match(struct ecore_hwfn *p_hwfn,
								u16 *modes_buf_offset)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	bool arg1, arg2;
	u8 tree_val;

	/* Get next element from modes tree buffer */
	tree_val = ((u8 *)s_dbg_arrays[BIN_BUF_DBG_MODE_TREE].ptr)[(*modes_buf_offset)++];

	switch (tree_val) {
	case INIT_MODE_OP_NOT:
		return !ecore_is_mode_match(p_hwfn, modes_buf_offset);
	case INIT_MODE_OP_OR:
	case INIT_MODE_OP_AND:
		arg1 = ecore_is_mode_match(p_hwfn, modes_buf_offset);
		arg2 = ecore_is_mode_match(p_hwfn, modes_buf_offset);
		return (tree_val == INIT_MODE_OP_OR) ? (arg1 || arg2) : (arg1 && arg2);
	default: return dev_data->mode_enable[tree_val - MAX_INIT_MODE_OPS] > 0;
	}
}