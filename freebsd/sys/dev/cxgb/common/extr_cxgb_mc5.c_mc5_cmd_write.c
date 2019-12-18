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
 int /*<<< orphan*/  A_MC5_DB_DBGI_REQ_CMD ; 
 int /*<<< orphan*/  A_MC5_DB_DBGI_RSP_STATUS ; 
 int /*<<< orphan*/  F_DBGIRSPVALID ; 
 int /*<<< orphan*/  MAX_WRITE_ATTEMPTS ; 
 int t3_wait_op_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mc5_cmd_write(adapter_t *adapter, u32 cmd)
{
	t3_write_reg(adapter, A_MC5_DB_DBGI_REQ_CMD, cmd);
	return t3_wait_op_done(adapter, A_MC5_DB_DBGI_RSP_STATUS,
			       F_DBGIRSPVALID, 1, MAX_WRITE_ATTEMPTS, 1);
}