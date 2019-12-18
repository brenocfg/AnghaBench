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
typedef  scalar_t__ u16 ;
struct fw_rss_ind_tbl_cmd {void* startidx; void* niqid; int /*<<< orphan*/  iq0_to_iq2; void* retval_len16; void* op_to_viid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int FW_LEN16 (struct fw_rss_ind_tbl_cmd) ; 
 int /*<<< orphan*/  FW_RSS_IND_TBL_CMD ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_CMD_WRITE ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_RSS_IND_TBL_CMD_IQ0 (scalar_t__) ; 
 int V_FW_RSS_IND_TBL_CMD_IQ1 (scalar_t__) ; 
 int V_FW_RSS_IND_TBL_CMD_IQ2 (scalar_t__) ; 
 int V_FW_RSS_IND_TBL_CMD_VIID (unsigned int) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_ind_tbl_cmd*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int t4_wr_mbox (struct adapter*,int,struct fw_rss_ind_tbl_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_config_rss_range(struct adapter *adapter, int mbox, unsigned int viid,
			int start, int n, const u16 *rspq, unsigned int nrspq)
{
	int ret;
	const u16 *rsp = rspq;
	const u16 *rsp_end = rspq + nrspq;
	struct fw_rss_ind_tbl_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(V_FW_CMD_OP(FW_RSS_IND_TBL_CMD) |
				     F_FW_CMD_REQUEST | F_FW_CMD_WRITE |
				     V_FW_RSS_IND_TBL_CMD_VIID(viid));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));

	/*
	 * Each firmware RSS command can accommodate up to 32 RSS Ingress
	 * Queue Identifiers.  These Ingress Queue IDs are packed three to
	 * a 32-bit word as 10-bit values with the upper remaining 2 bits
	 * reserved.
	 */
	while (n > 0) {
		int nq = min(n, 32);
		int nq_packed = 0;
		__be32 *qp = &cmd.iq0_to_iq2;

		/*
		 * Set up the firmware RSS command header to send the next
		 * "nq" Ingress Queue IDs to the firmware.
		 */
		cmd.niqid = cpu_to_be16(nq);
		cmd.startidx = cpu_to_be16(start);

		/*
		 * "nq" more done for the start of the next loop.
		 */
		start += nq;
		n -= nq;

		/*
		 * While there are still Ingress Queue IDs to stuff into the
		 * current firmware RSS command, retrieve them from the
		 * Ingress Queue ID array and insert them into the command.
		 */
		while (nq > 0) {
			/*
			 * Grab up to the next 3 Ingress Queue IDs (wrapping
			 * around the Ingress Queue ID array if necessary) and
			 * insert them into the firmware RSS command at the
			 * current 3-tuple position within the commad.
			 */
			u16 qbuf[3];
			u16 *qbp = qbuf;
			int nqbuf = min(3, nq);

			nq -= nqbuf;
			qbuf[0] = qbuf[1] = qbuf[2] = 0;
			while (nqbuf && nq_packed < 32) {
				nqbuf--;
				nq_packed++;
				*qbp++ = *rsp++;
				if (rsp >= rsp_end)
					rsp = rspq;
			}
			*qp++ = cpu_to_be32(V_FW_RSS_IND_TBL_CMD_IQ0(qbuf[0]) |
					    V_FW_RSS_IND_TBL_CMD_IQ1(qbuf[1]) |
					    V_FW_RSS_IND_TBL_CMD_IQ2(qbuf[2]));
		}

		/*
		 * Send this portion of the RRS table update to the firmware;
		 * bail out on any errors.
		 */
		ret = t4_wr_mbox(adapter, mbox, &cmd, sizeof(cmd), NULL);
		if (ret)
			return ret;
	}
	return 0;
}