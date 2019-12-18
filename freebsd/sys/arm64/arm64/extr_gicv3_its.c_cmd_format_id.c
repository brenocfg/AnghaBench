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
struct its_cmd {int /*<<< orphan*/ * cmd_dword; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ID_MASK ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
cmd_format_id(struct its_cmd *cmd, uint32_t id)
{
	/* ID field: DW1 [31:0] */
	cmd->cmd_dword[1] &= htole64(~CMD_ID_MASK);
	cmd->cmd_dword[1] |= htole64(id);
}