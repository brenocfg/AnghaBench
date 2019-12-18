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
typedef  scalar_t__ u32 ;
struct socfpga_fpga_priv {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_DCLKCNT_OFST ; 
 scalar_t__ SOCFPGA_FPGMGR_DCLKSTAT_DCNTDONE_E_DONE ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_DCLKSTAT_OFST ; 
 int /*<<< orphan*/  socfpga_fpga_clear_done_status (struct socfpga_fpga_priv*) ; 
 scalar_t__ socfpga_fpga_readl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socfpga_fpga_writel (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int socfpga_fpga_dclk_set_and_wait_clear(struct socfpga_fpga_priv *priv,
						u32 count)
{
	int timeout = 2;
	u32 done;

	/* Clear any existing DONE status. */
	if (socfpga_fpga_readl(priv, SOCFPGA_FPGMGR_DCLKSTAT_OFST))
		socfpga_fpga_clear_done_status(priv);

	/* Issue the DCLK count. */
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_DCLKCNT_OFST, count);

	/* Poll DCLKSTAT to see if it completed in the timeout period. */
	do {
		done = socfpga_fpga_readl(priv, SOCFPGA_FPGMGR_DCLKSTAT_OFST);
		if (done == SOCFPGA_FPGMGR_DCLKSTAT_DCNTDONE_E_DONE) {
			socfpga_fpga_clear_done_status(priv);
			return 0;
		}
		udelay(1);
	} while (timeout--);

	return -ETIMEDOUT;
}