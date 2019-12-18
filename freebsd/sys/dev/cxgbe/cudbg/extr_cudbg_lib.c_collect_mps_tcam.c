#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct fw_ldst_mps_rplc {int /*<<< orphan*/  rplc255_224; int /*<<< orphan*/  rplc223_192; int /*<<< orphan*/  rplc191_160; int /*<<< orphan*/  rplc159_128; int /*<<< orphan*/  rplc127_96; int /*<<< orphan*/  rplc95_64; int /*<<< orphan*/  rplc63_32; int /*<<< orphan*/  rplc31_0; int /*<<< orphan*/  fid_idx; } ;
struct TYPE_5__ {struct fw_ldst_mps_rplc rplc; } ;
struct TYPE_6__ {TYPE_2__ mps; } ;
struct fw_ldst_cmd {TYPE_3__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct cudbg_mps_tcam {scalar_t__ lookup_type; int vniy; int dip_hit; int vlan_vld; int ivlan; int vnix; int cls_lo; int cls_hi; int repli; int idx; scalar_t__ rplc_size; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; void** rplc; int /*<<< orphan*/  port_num; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {int size; struct fw_ldst_cmd* data; } ;
struct adapter {TYPE_1__* chip_params; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  ldst_cmd ;
struct TYPE_4__ {int mps_tcam_size; scalar_t__ mps_rplc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MPS_CLS_TCAM_DATA2_CTL ; 
 int /*<<< orphan*/  A_MPS_CLS_TCAM_RDATA0_REQ_ID1 ; 
 int /*<<< orphan*/  A_MPS_CLS_TCAM_RDATA1_REQ_ID1 ; 
 int /*<<< orphan*/  A_MPS_CLS_TCAM_RDATA2_REQ_ID1 ; 
 scalar_t__ CHELSIO_T6 ; 
 scalar_t__ CUDBG_MAX_RPLC_SIZE ; 
 int CUDBG_SYSTEM_ERROR ; 
 int /*<<< orphan*/  FW_LDST_ADDRSPC_MPS ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int /*<<< orphan*/  FW_LDST_MPS_RPLC ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 int F_DATADIPHIT ; 
 int F_DATAVIDH2 ; 
 int F_FW_CMD_READ ; 
 int F_FW_CMD_REQUEST ; 
 int F_REPLICATE ; 
 int F_T6_REPLICATE ; 
 scalar_t__ G_DATALKPTYPE (int) ; 
 int /*<<< orphan*/  G_DATAPORTNUM (int) ; 
 int G_DATAVIDH1 (int) ; 
 int G_DMACH (int) ; 
 int G_VIDL (int) ; 
 int INTR_OK ; 
 int /*<<< orphan*/  MPS_CLS_SRAM_H (int) ; 
 int /*<<< orphan*/  MPS_CLS_SRAM_L (int) ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_X_L (int) ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_Y_L (int) ; 
 scalar_t__ M_DATALKPTYPE ; 
 int SLEEP_OK ; 
 int V_CTLCMDTYPE (int /*<<< orphan*/ ) ; 
 int V_CTLREQID (int) ; 
 int V_CTLTCAMINDEX (int) ; 
 int V_CTLTCAMSEL (int) ; 
 int V_CTLXYBITSEL (int) ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_LDST_CMD_ADDRSPACE (int /*<<< orphan*/ ) ; 
 int V_FW_LDST_CMD_FID (int /*<<< orphan*/ ) ; 
 int V_FW_LDST_CMD_IDX (int) ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  cudbg_tcamxy2valmask (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ is_t5 (struct adapter*) ; 
 scalar_t__ is_t6 (struct adapter*) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mps_rpl_backdoor (struct adapter*,struct fw_ldst_mps_rplc*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_read_reg64 (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_mps_tcam(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
	struct cudbg_buffer scratch_buff;
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_mps_tcam *tcam = NULL;
	u32 size = 0, i, n, total_size = 0;
	u32 ctl, data2;
	u64 tcamy, tcamx, val;
	int rc;

	n = padap->chip_params->mps_tcam_size;
	size = sizeof(struct cudbg_mps_tcam) * n;
	scratch_buff.size = size;

	rc = get_scratch_buff(dbg_buff, scratch_buff.size, &scratch_buff);
	if (rc)
		goto err;
	memset(scratch_buff.data, 0, size);

	tcam = (struct cudbg_mps_tcam *)scratch_buff.data;
	for (i = 0; i < n; i++) {
		if (chip_id(padap) >= CHELSIO_T6) {
			/* CtlReqID   - 1: use Host Driver Requester ID
			 * CtlCmdType - 0: Read, 1: Write
			 * CtlTcamSel - 0: TCAM0, 1: TCAM1
			 * CtlXYBitSel- 0: Y bit, 1: X bit
			 */

			/* Read tcamy */
			ctl = (V_CTLREQID(1) |
			       V_CTLCMDTYPE(0) | V_CTLXYBITSEL(0));
			if (i < 256)
				ctl |= V_CTLTCAMINDEX(i) | V_CTLTCAMSEL(0);
			else
				ctl |= V_CTLTCAMINDEX(i - 256) |
				       V_CTLTCAMSEL(1);

			t4_write_reg(padap, A_MPS_CLS_TCAM_DATA2_CTL, ctl);
			val = t4_read_reg(padap, A_MPS_CLS_TCAM_RDATA1_REQ_ID1);
			tcamy = G_DMACH(val) << 32;
			tcamy |= t4_read_reg(padap, A_MPS_CLS_TCAM_RDATA0_REQ_ID1);
			data2 = t4_read_reg(padap, A_MPS_CLS_TCAM_RDATA2_REQ_ID1);
			tcam->lookup_type = G_DATALKPTYPE(data2);

			/* 0 - Outer header, 1 - Inner header
			 * [71:48] bit locations are overloaded for
			 * outer vs. inner lookup types.
			 */

			if (tcam->lookup_type &&
			    (tcam->lookup_type != M_DATALKPTYPE)) {
				/* Inner header VNI */
				tcam->vniy = ((data2 & F_DATAVIDH2) << 23) |
					     (G_DATAVIDH1(data2) << 16) |
					     G_VIDL(val);
				tcam->dip_hit = data2 & F_DATADIPHIT;
			} else {
				tcam->vlan_vld = data2 & F_DATAVIDH2;
				tcam->ivlan = G_VIDL(val);
			}

			tcam->port_num = G_DATAPORTNUM(data2);

			/* Read tcamx. Change the control param */
			ctl |= V_CTLXYBITSEL(1);
			t4_write_reg(padap, A_MPS_CLS_TCAM_DATA2_CTL, ctl);
			val = t4_read_reg(padap, A_MPS_CLS_TCAM_RDATA1_REQ_ID1);
			tcamx = G_DMACH(val) << 32;
			tcamx |= t4_read_reg(padap, A_MPS_CLS_TCAM_RDATA0_REQ_ID1);
			data2 = t4_read_reg(padap, A_MPS_CLS_TCAM_RDATA2_REQ_ID1);
			if (tcam->lookup_type &&
			    (tcam->lookup_type != M_DATALKPTYPE)) {
				/* Inner header VNI mask */
				tcam->vnix = ((data2 & F_DATAVIDH2) << 23) |
					     (G_DATAVIDH1(data2) << 16) |
					     G_VIDL(val);
			}
		} else {
			tcamy = t4_read_reg64(padap, MPS_CLS_TCAM_Y_L(i));
			tcamx = t4_read_reg64(padap, MPS_CLS_TCAM_X_L(i));
		}

		if (tcamx & tcamy)
			continue;

		tcam->cls_lo = t4_read_reg(padap, MPS_CLS_SRAM_L(i));
		tcam->cls_hi = t4_read_reg(padap, MPS_CLS_SRAM_H(i));

		if (is_t5(padap))
			tcam->repli = (tcam->cls_lo & F_REPLICATE);
		else if (is_t6(padap))
			tcam->repli = (tcam->cls_lo & F_T6_REPLICATE);

		if (tcam->repli) {
			struct fw_ldst_cmd ldst_cmd;
			struct fw_ldst_mps_rplc mps_rplc;

			memset(&ldst_cmd, 0, sizeof(ldst_cmd));
			ldst_cmd.op_to_addrspace =
				htonl(V_FW_CMD_OP(FW_LDST_CMD) |
				      F_FW_CMD_REQUEST |
				      F_FW_CMD_READ |
				      V_FW_LDST_CMD_ADDRSPACE(
					      FW_LDST_ADDRSPC_MPS));

			ldst_cmd.cycles_to_len16 = htonl(FW_LEN16(ldst_cmd));

			ldst_cmd.u.mps.rplc.fid_idx =
				htons(V_FW_LDST_CMD_FID(FW_LDST_MPS_RPLC) |
				      V_FW_LDST_CMD_IDX(i));

			rc = begin_synchronized_op(padap, NULL,
			    SLEEP_OK | INTR_OK, "t4cudm");
			if (rc == 0) {
				rc = t4_wr_mbox(padap, padap->mbox, &ldst_cmd,
						sizeof(ldst_cmd), &ldst_cmd);
				end_synchronized_op(padap, 0);
			}

			if (rc)
				mps_rpl_backdoor(padap, &mps_rplc);
			else
				mps_rplc = ldst_cmd.u.mps.rplc;

			tcam->rplc[0] = ntohl(mps_rplc.rplc31_0);
			tcam->rplc[1] = ntohl(mps_rplc.rplc63_32);
			tcam->rplc[2] = ntohl(mps_rplc.rplc95_64);
			tcam->rplc[3] = ntohl(mps_rplc.rplc127_96);
			if (padap->chip_params->mps_rplc_size >
					CUDBG_MAX_RPLC_SIZE) {
				tcam->rplc[4] = ntohl(mps_rplc.rplc159_128);
				tcam->rplc[5] = ntohl(mps_rplc.rplc191_160);
				tcam->rplc[6] = ntohl(mps_rplc.rplc223_192);
				tcam->rplc[7] = ntohl(mps_rplc.rplc255_224);
			}
		}
		cudbg_tcamxy2valmask(tcamx, tcamy, tcam->addr, &tcam->mask);

		tcam->idx = i;
		tcam->rplc_size = padap->chip_params->mps_rplc_size;

		total_size += sizeof(struct cudbg_mps_tcam);

		tcam++;
	}

	if (total_size == 0) {
		rc = CUDBG_SYSTEM_ERROR;
		goto err1;
	}

	scratch_buff.size = total_size;
	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);

err1:
	scratch_buff.size = size;
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;
}