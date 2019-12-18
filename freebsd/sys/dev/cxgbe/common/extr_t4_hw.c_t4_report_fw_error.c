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
typedef  int u32 ;
struct adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_FW ; 
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*,char const* const,int) ; 
 int /*<<< orphan*/  FW_OK ; 
 int F_PCIE_FW_ERR ; 
 size_t G_PCIE_FW_EVAL (int) ; 
 int /*<<< orphan*/  t4_os_dump_devlog (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t4_report_fw_error(struct adapter *adap)
{
	static const char *const reason[] = {
		"Crash",			/* PCIE_FW_EVAL_CRASH */
		"During Device Preparation",	/* PCIE_FW_EVAL_PREP */
		"During Device Configuration",	/* PCIE_FW_EVAL_CONF */
		"During Device Initialization",	/* PCIE_FW_EVAL_INIT */
		"Unexpected Event",		/* PCIE_FW_EVAL_UNEXPECTEDEVENT */
		"Insufficient Airflow",		/* PCIE_FW_EVAL_OVERHEAT */
		"Device Shutdown",		/* PCIE_FW_EVAL_DEVICESHUTDOWN */
		"Reserved",			/* reserved */
	};
	u32 pcie_fw;

	pcie_fw = t4_read_reg(adap, A_PCIE_FW);
	if (pcie_fw & F_PCIE_FW_ERR) {
		adap->flags &= ~FW_OK;
		CH_ERR(adap, "firmware reports adapter error: %s (0x%08x)\n",
		    reason[G_PCIE_FW_EVAL(pcie_fw)], pcie_fw);
		if (pcie_fw != 0xffffffff)
			t4_os_dump_devlog(adap);
	}
}