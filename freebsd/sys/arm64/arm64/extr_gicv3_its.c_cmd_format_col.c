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
typedef  int /*<<< orphan*/  uint16_t ;
struct its_cmd {int /*<<< orphan*/ * cmd_dword; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_COL_MASK ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
cmd_format_col(struct its_cmd *cmd, uint16_t col_id)
{
	/* Collection field: DW2 [16:0] */
	cmd->cmd_dword[2] &= htole64(~CMD_COL_MASK);
	cmd->cmd_dword[2] |= htole64(col_id);
}