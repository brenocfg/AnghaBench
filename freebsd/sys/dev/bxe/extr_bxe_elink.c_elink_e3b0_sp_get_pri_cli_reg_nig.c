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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  elink_e3b0_sp_get_pri_cli_reg (int const,int const,int const,int const,int) ; 

__attribute__((used)) static uint64_t elink_e3b0_sp_get_pri_cli_reg_nig(const uint8_t cos, const uint8_t pri_set)
{
	/* MCP Dbg0 and dbg1 are always with higher strict pri*/
	const uint8_t nig_cos_offset = 3;
	const uint8_t nig_pri_offset = 3;

	return elink_e3b0_sp_get_pri_cli_reg(cos, nig_cos_offset, pri_set,
		nig_pri_offset, 4);

}