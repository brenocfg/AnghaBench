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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct port_tx_state {int dummy; } ;
struct fw_debug_cmd {int dummy; } ;
struct adapter {int flags; } ;
typedef  int /*<<< orphan*/  cmd_rpl ;
typedef  int const __be64 ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  ASSERT_SYNCHRONIZED_OP (struct adapter*) ; 
 int /*<<< orphan*/  A_CIM_PF_MAILBOX_CTRL ; 
 int /*<<< orphan*/  A_CIM_PF_MAILBOX_DATA ; 
 int /*<<< orphan*/  A_CIM_VF_EXT_MAILBOX_CTRL ; 
 int A_PCIE_FW ; 
 int CHK_MBOX_ACCESS ; 
 int /*<<< orphan*/  CH_DUMP_MBOX (struct adapter*,int,int,char*,int const*,int) ; 
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*,int /*<<< orphan*/  const,int,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 scalar_t__ FW_DEBUG_CMD ; 
 int FW_T4VF_MBDATA_BASE_ADDR ; 
 int FW_T6VF_MBDATA_BASE_ADDR ; 
 int F_MBMSGVALID ; 
 int F_PCIE_FW_ERR ; 
 scalar_t__ G_FW_CMD_OP (int) ; 
 int G_FW_CMD_RETVAL (int) ; 
 int G_MBOWNER (int) ; 
 int IS_VF ; 
 int MAX_NPORTS ; 
 int MBOX_LEN ; 
 int PF_REG (int,int /*<<< orphan*/ ) ; 
 int VF_CIM_REG (int /*<<< orphan*/ ) ; 
 int V_FW_CMD_RETVAL (int /*<<< orphan*/ ) ; 
 int V_MBOWNER (int) ; 
 int X_CIM_PF_NOACCESS ; 
 int X_MBOWNER_FW ; 
 int X_MBOWNER_NONE ; 
 int X_MBOWNER_PL ; 
 int be64_to_cpu (int const) ; 
 int /*<<< orphan*/  check_tx_state (struct adapter*,struct port_tx_state*) ; 
 int /*<<< orphan*/  fw_asrt (struct adapter*,struct fw_debug_cmd*) ; 
 int /*<<< orphan*/  get_mbox_rpl (struct adapter*,int const*,int,int) ; 
 scalar_t__ is_t6 (struct adapter*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 int /*<<< orphan*/  memset (int const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  read_tx_state (struct adapter*,struct port_tx_state*) ; 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_os_dump_devlog (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_report_fw_error (struct adapter*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int) ; 
 int /*<<< orphan*/  t4_write_reg64 (struct adapter*,int,int) ; 

int t4_wr_mbox_meat_timeout(struct adapter *adap, int mbox, const void *cmd,
			    int size, void *rpl, bool sleep_ok, int timeout)
{
	/*
	 * We delay in small increments at first in an effort to maintain
	 * responsiveness for simple, fast executing commands but then back
	 * off to larger delays to a maximum retry delay.
	 */
	static const int delay[] = {
		1, 1, 3, 5, 10, 10, 20, 50, 100
	};
	u32 v;
	u64 res;
	int i, ms, delay_idx, ret, next_tx_check;
	u32 data_reg = PF_REG(mbox, A_CIM_PF_MAILBOX_DATA);
	u32 ctl_reg = PF_REG(mbox, A_CIM_PF_MAILBOX_CTRL);
	u32 ctl;
	__be64 cmd_rpl[MBOX_LEN/8];
	u32 pcie_fw;
	struct port_tx_state tx_state[MAX_NPORTS];

	if (adap->flags & CHK_MBOX_ACCESS)
		ASSERT_SYNCHRONIZED_OP(adap);

	if (size <= 0 || (size & 15) || size > MBOX_LEN)
		return -EINVAL;

	if (adap->flags & IS_VF) {
		if (is_t6(adap))
			data_reg = FW_T6VF_MBDATA_BASE_ADDR;
		else
			data_reg = FW_T4VF_MBDATA_BASE_ADDR;
		ctl_reg = VF_CIM_REG(A_CIM_VF_EXT_MAILBOX_CTRL);
	}

	/*
	 * If we have a negative timeout, that implies that we can't sleep.
	 */
	if (timeout < 0) {
		sleep_ok = false;
		timeout = -timeout;
	}

	/*
	 * Attempt to gain access to the mailbox.
	 */
	for (i = 0; i < 4; i++) {
		ctl = t4_read_reg(adap, ctl_reg);
		v = G_MBOWNER(ctl);
		if (v != X_MBOWNER_NONE)
			break;
	}

	/*
	 * If we were unable to gain access, report the error to our caller.
	 */
	if (v != X_MBOWNER_PL) {
		t4_report_fw_error(adap);
		ret = (v == X_MBOWNER_FW) ? -EBUSY : -ETIMEDOUT;
		return ret;
	}

	/*
	 * If we gain ownership of the mailbox and there's a "valid" message
	 * in it, this is likely an asynchronous error message from the
	 * firmware.  So we'll report that and then proceed on with attempting
	 * to issue our own command ... which may well fail if the error
	 * presaged the firmware crashing ...
	 */
	if (ctl & F_MBMSGVALID) {
		CH_DUMP_MBOX(adap, mbox, data_reg, "VLD", NULL, true);
	}

	/*
	 * Copy in the new mailbox command and send it on its way ...
	 */
	memset(cmd_rpl, 0, sizeof(cmd_rpl));
	memcpy(cmd_rpl, cmd, size);
	CH_DUMP_MBOX(adap, mbox, 0, "cmd", cmd_rpl, false);
	for (i = 0; i < ARRAY_SIZE(cmd_rpl); i++)
		t4_write_reg64(adap, data_reg + i * 8, be64_to_cpu(cmd_rpl[i]));

	if (adap->flags & IS_VF) {
		/*
		 * For the VFs, the Mailbox Data "registers" are
		 * actually backed by T4's "MA" interface rather than
		 * PL Registers (as is the case for the PFs).  Because
		 * these are in different coherency domains, the write
		 * to the VF's PL-register-backed Mailbox Control can
		 * race in front of the writes to the MA-backed VF
		 * Mailbox Data "registers".  So we need to do a
		 * read-back on at least one byte of the VF Mailbox
		 * Data registers before doing the write to the VF
		 * Mailbox Control register.
		 */
		t4_read_reg(adap, data_reg);
	}

	t4_write_reg(adap, ctl_reg, F_MBMSGVALID | V_MBOWNER(X_MBOWNER_FW));
	read_tx_state(adap, &tx_state[0]);	/* also flushes the write_reg */
	next_tx_check = 1000;
	delay_idx = 0;
	ms = delay[0];

	/*
	 * Loop waiting for the reply; bail out if we time out or the firmware
	 * reports an error.
	 */
	pcie_fw = 0;
	for (i = 0; i < timeout; i += ms) {
		if (!(adap->flags & IS_VF)) {
			pcie_fw = t4_read_reg(adap, A_PCIE_FW);
			if (pcie_fw & F_PCIE_FW_ERR)
				break;
		}

		if (i >= next_tx_check) {
			check_tx_state(adap, &tx_state[0]);
			next_tx_check = i + 1000;
		}

		if (sleep_ok) {
			ms = delay[delay_idx];  /* last element may repeat */
			if (delay_idx < ARRAY_SIZE(delay) - 1)
				delay_idx++;
			msleep(ms);
		} else {
			mdelay(ms);
		}

		v = t4_read_reg(adap, ctl_reg);
		if (v == X_CIM_PF_NOACCESS)
			continue;
		if (G_MBOWNER(v) == X_MBOWNER_PL) {
			if (!(v & F_MBMSGVALID)) {
				t4_write_reg(adap, ctl_reg,
					     V_MBOWNER(X_MBOWNER_NONE));
				continue;
			}

			/*
			 * Retrieve the command reply and release the mailbox.
			 */
			get_mbox_rpl(adap, cmd_rpl, MBOX_LEN/8, data_reg);
			CH_DUMP_MBOX(adap, mbox, 0, "rpl", cmd_rpl, false);
			t4_write_reg(adap, ctl_reg, V_MBOWNER(X_MBOWNER_NONE));

			res = be64_to_cpu(cmd_rpl[0]);
			if (G_FW_CMD_OP(res >> 32) == FW_DEBUG_CMD) {
				fw_asrt(adap, (struct fw_debug_cmd *)cmd_rpl);
				res = V_FW_CMD_RETVAL(EIO);
			} else if (rpl)
				memcpy(rpl, cmd_rpl, size);
			return -G_FW_CMD_RETVAL((int)res);
		}
	}

	/*
	 * We timed out waiting for a reply to our mailbox command.  Report
	 * the error and also check to see if the firmware reported any
	 * errors ...
	 */
	CH_ERR(adap, "command %#x in mbox %d timed out (0x%08x).\n",
	    *(const u8 *)cmd, mbox, pcie_fw);
	CH_DUMP_MBOX(adap, mbox, 0, "cmdsent", cmd_rpl, true);
	CH_DUMP_MBOX(adap, mbox, data_reg, "current", NULL, true);

	if (pcie_fw & F_PCIE_FW_ERR) {
		ret = -ENXIO;
		t4_report_fw_error(adap);
	} else {
		ret = -ETIMEDOUT;
		t4_os_dump_devlog(adap);
	}

	t4_fatal_err(adap, true);
	return ret;
}