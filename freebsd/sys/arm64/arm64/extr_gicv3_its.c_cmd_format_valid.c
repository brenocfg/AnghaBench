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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
struct its_cmd {int /*<<< orphan*/ * cmd_dword; } ;

/* Variables and functions */
 int CMD_VALID_MASK ; 
 int CMD_VALID_SHIFT ; 
 int /*<<< orphan*/  htole64 (int) ; 

__attribute__((used)) static __inline void
cmd_format_valid(struct its_cmd *cmd, uint8_t valid)
{
	/* Valid field: DW2 [63] */
	cmd->cmd_dword[2] &= htole64(~CMD_VALID_MASK);
	cmd->cmd_dword[2] |= htole64((uint64_t)valid << CMD_VALID_SHIFT);
}