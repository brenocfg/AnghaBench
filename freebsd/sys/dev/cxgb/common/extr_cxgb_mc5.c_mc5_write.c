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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_MC5_DB_DBGI_REQ_ADDR0 ; 
 int /*<<< orphan*/  CH_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mc5_cmd_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mc5_write(adapter_t *adapter, u32 addr_lo, u32 cmd)
{
	t3_write_reg(adapter, A_MC5_DB_DBGI_REQ_ADDR0, addr_lo);
	if (mc5_cmd_write(adapter, cmd) == 0)
		return 0;
	CH_ERR(adapter, "MC5 timeout writing to TCAM address 0x%x\n", addr_lo);
	return -1;
}