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
struct fw_watchdog_cmd {void* action; void* timeout; void* retval_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 unsigned int FW_LEN16 (struct fw_watchdog_cmd) ; 
 int /*<<< orphan*/  FW_WATCHDOG_CMD ; 
 unsigned int F_FW_CMD_REQUEST ; 
 unsigned int F_FW_CMD_WRITE ; 
 unsigned int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 unsigned int V_FW_PARAMS_CMD_PFN (unsigned int) ; 
 unsigned int V_FW_PARAMS_CMD_VFN (unsigned int) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_watchdog_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_watchdog_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_config_watchdog(struct adapter *adapter, unsigned int mbox,
		       unsigned int pf, unsigned int vf,
		       unsigned int timeout, unsigned int action)
{
	struct fw_watchdog_cmd wdog;
	unsigned int ticks;

	/*
	 * The watchdog command expects a timeout in units of 10ms so we need
	 * to convert it here (via rounding) and force a minimum of one 10ms
	 * "tick" if the timeout is non-zero but the conversion results in 0
	 * ticks.
	 */
	ticks = (timeout + 5)/10;
	if (timeout && !ticks)
		ticks = 1;

	memset(&wdog, 0, sizeof wdog);
	wdog.op_to_vfn = cpu_to_be32(V_FW_CMD_OP(FW_WATCHDOG_CMD) |
				     F_FW_CMD_REQUEST |
				     F_FW_CMD_WRITE |
				     V_FW_PARAMS_CMD_PFN(pf) |
				     V_FW_PARAMS_CMD_VFN(vf));
	wdog.retval_len16 = cpu_to_be32(FW_LEN16(wdog));
	wdog.timeout = cpu_to_be32(ticks);
	wdog.action = cpu_to_be32(action);

	return t4_wr_mbox(adapter, mbox, &wdog, sizeof wdog, NULL);
}