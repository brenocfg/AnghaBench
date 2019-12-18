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
struct fw_hello_cmd {int /*<<< orphan*/  err_to_clearinit; } ;
struct adapter {int dummy; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;
typedef  enum dev_master { ____Placeholder_dev_master } dev_master ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_FW ; 
 int DEV_STATE_ERR ; 
 int DEV_STATE_INIT ; 
 int DEV_STATE_UNINIT ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int FW_CMD_HELLO_RETRIES ; 
 int FW_CMD_HELLO_TIMEOUT ; 
 int /*<<< orphan*/  FW_HELLO_CMD_STAGE_OS ; 
 int FW_SUCCESS ; 
 int F_FW_HELLO_CMD_CLEARINIT ; 
 int F_FW_HELLO_CMD_ERR ; 
 int F_FW_HELLO_CMD_INIT ; 
 int F_PCIE_FW_ERR ; 
 int F_PCIE_FW_INIT ; 
 int F_PCIE_FW_MASTER_VLD ; 
 unsigned int G_FW_HELLO_CMD_MBMASTER (int) ; 
 unsigned int G_PCIE_FW_MASTER (int) ; 
 int /*<<< orphan*/  HELLO ; 
 int /*<<< orphan*/  INIT_CMD (struct fw_hello_cmd,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MASTER_CANT ; 
 int MASTER_MUST ; 
 unsigned int M_FW_HELLO_CMD_MBMASTER ; 
 unsigned int M_PCIE_FW_MASTER ; 
 int V_FW_HELLO_CMD_MASTERDIS (int) ; 
 int V_FW_HELLO_CMD_MASTERFORCE (int) ; 
 int V_FW_HELLO_CMD_MBASYNCNOT (unsigned int) ; 
 int V_FW_HELLO_CMD_MBMASTER (unsigned int) ; 
 int V_FW_HELLO_CMD_STAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_hello_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_report_fw_error (struct adapter*) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_hello_cmd*,int,struct fw_hello_cmd*) ; 

int t4_fw_hello(struct adapter *adap, unsigned int mbox, unsigned int evt_mbox,
		enum dev_master master, enum dev_state *state)
{
	int ret;
	struct fw_hello_cmd c;
	u32 v;
	unsigned int master_mbox;
	int retries = FW_CMD_HELLO_RETRIES;

retry:
	memset(&c, 0, sizeof(c));
	INIT_CMD(c, HELLO, WRITE);
	c.err_to_clearinit = cpu_to_be32(
		V_FW_HELLO_CMD_MASTERDIS(master == MASTER_CANT) |
		V_FW_HELLO_CMD_MASTERFORCE(master == MASTER_MUST) |
		V_FW_HELLO_CMD_MBMASTER(master == MASTER_MUST ?
					mbox : M_FW_HELLO_CMD_MBMASTER) |
		V_FW_HELLO_CMD_MBASYNCNOT(evt_mbox) |
		V_FW_HELLO_CMD_STAGE(FW_HELLO_CMD_STAGE_OS) |
		F_FW_HELLO_CMD_CLEARINIT);

	/*
	 * Issue the HELLO command to the firmware.  If it's not successful
	 * but indicates that we got a "busy" or "timeout" condition, retry
	 * the HELLO until we exhaust our retry limit.  If we do exceed our
	 * retry limit, check to see if the firmware left us any error
	 * information and report that if so ...
	 */
	ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), &c);
	if (ret != FW_SUCCESS) {
		if ((ret == -EBUSY || ret == -ETIMEDOUT) && retries-- > 0)
			goto retry;
		if (t4_read_reg(adap, A_PCIE_FW) & F_PCIE_FW_ERR)
			t4_report_fw_error(adap);
		return ret;
	}

	v = be32_to_cpu(c.err_to_clearinit);
	master_mbox = G_FW_HELLO_CMD_MBMASTER(v);
	if (state) {
		if (v & F_FW_HELLO_CMD_ERR)
			*state = DEV_STATE_ERR;
		else if (v & F_FW_HELLO_CMD_INIT)
			*state = DEV_STATE_INIT;
		else
			*state = DEV_STATE_UNINIT;
	}

	/*
	 * If we're not the Master PF then we need to wait around for the
	 * Master PF Driver to finish setting up the adapter.
	 *
	 * Note that we also do this wait if we're a non-Master-capable PF and
	 * there is no current Master PF; a Master PF may show up momentarily
	 * and we wouldn't want to fail pointlessly.  (This can happen when an
	 * OS loads lots of different drivers rapidly at the same time).  In
	 * this case, the Master PF returned by the firmware will be
	 * M_PCIE_FW_MASTER so the test below will work ...
	 */
	if ((v & (F_FW_HELLO_CMD_ERR|F_FW_HELLO_CMD_INIT)) == 0 &&
	    master_mbox != mbox) {
		int waiting = FW_CMD_HELLO_TIMEOUT;

		/*
		 * Wait for the firmware to either indicate an error or
		 * initialized state.  If we see either of these we bail out
		 * and report the issue to the caller.  If we exhaust the
		 * "hello timeout" and we haven't exhausted our retries, try
		 * again.  Otherwise bail with a timeout error.
		 */
		for (;;) {
			u32 pcie_fw;

			msleep(50);
			waiting -= 50;

			/*
			 * If neither Error nor Initialialized are indicated
			 * by the firmware keep waiting till we exhaust our
			 * timeout ... and then retry if we haven't exhausted
			 * our retries ...
			 */
			pcie_fw = t4_read_reg(adap, A_PCIE_FW);
			if (!(pcie_fw & (F_PCIE_FW_ERR|F_PCIE_FW_INIT))) {
				if (waiting <= 0) {
					if (retries-- > 0)
						goto retry;

					return -ETIMEDOUT;
				}
				continue;
			}

			/*
			 * We either have an Error or Initialized condition
			 * report errors preferentially.
			 */
			if (state) {
				if (pcie_fw & F_PCIE_FW_ERR)
					*state = DEV_STATE_ERR;
				else if (pcie_fw & F_PCIE_FW_INIT)
					*state = DEV_STATE_INIT;
			}

			/*
			 * If we arrived before a Master PF was selected and
			 * there's not a valid Master PF, grab its identity
			 * for our caller.
			 */
			if (master_mbox == M_PCIE_FW_MASTER &&
			    (pcie_fw & F_PCIE_FW_MASTER_VLD))
				master_mbox = G_PCIE_FW_MASTER(pcie_fw);
			break;
		}
	}

	return master_mbox;
}