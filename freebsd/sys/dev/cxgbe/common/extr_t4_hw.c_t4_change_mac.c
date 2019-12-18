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
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct fw_vi_mac_exact {int /*<<< orphan*/  valid_to_idx; int /*<<< orphan*/  macaddr; } ;
struct TYPE_4__ {struct fw_vi_mac_exact* exact; } ;
struct fw_vi_mac_cmd {void* op_to_viid; void* freemacs_to_len16; TYPE_1__ u; } ;
struct TYPE_6__ {scalar_t__ viid_smt_extn_support; } ;
struct adapter {TYPE_3__ params; TYPE_2__* chip_params; } ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_5__ {unsigned int mps_tcam_size; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_T5 ; 
 int ENOMEM ; 
 int FW_VI_MAC_ADD_MAC ; 
 int FW_VI_MAC_ADD_PERSIST_MAC ; 
 int /*<<< orphan*/  FW_VI_MAC_CMD ; 
 int FW_VI_MAC_MPS_TCAM_ENTRY ; 
 int FW_VI_MAC_SMT_AND_MPSTCAM ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_CMD_WRITE ; 
 int F_FW_VI_MAC_CMD_VALID ; 
 int G_FW_VI_MAC_CMD_IDX (int /*<<< orphan*/ ) ; 
 unsigned int G_FW_VI_MAC_CMD_SMTID (int /*<<< orphan*/ ) ; 
 unsigned int M_FW_VIID_VIN ; 
 int V_FW_CMD_LEN16 (int) ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_VI_MAC_CMD_IDX (int) ; 
 int V_FW_VI_MAC_CMD_SMAC_RESULT (int) ; 
 int V_FW_VI_MAC_CMD_VIID (unsigned int) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (struct fw_vi_mac_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_vi_mac_cmd*,int,struct fw_vi_mac_cmd*) ; 

int t4_change_mac(struct adapter *adap, unsigned int mbox, unsigned int viid,
		  int idx, const u8 *addr, bool persist, uint16_t *smt_idx)
{
	int ret, mode;
	struct fw_vi_mac_cmd c;
	struct fw_vi_mac_exact *p = c.u.exact;
	unsigned int max_mac_addr = adap->chip_params->mps_tcam_size;

	if (idx < 0)		/* new allocation */
		idx = persist ? FW_VI_MAC_ADD_PERSIST_MAC : FW_VI_MAC_ADD_MAC;
	mode = smt_idx ? FW_VI_MAC_SMT_AND_MPSTCAM : FW_VI_MAC_MPS_TCAM_ENTRY;

	memset(&c, 0, sizeof(c));
	c.op_to_viid = cpu_to_be32(V_FW_CMD_OP(FW_VI_MAC_CMD) |
				   F_FW_CMD_REQUEST | F_FW_CMD_WRITE |
				   V_FW_VI_MAC_CMD_VIID(viid));
	c.freemacs_to_len16 = cpu_to_be32(V_FW_CMD_LEN16(1));
	p->valid_to_idx = cpu_to_be16(F_FW_VI_MAC_CMD_VALID |
				      V_FW_VI_MAC_CMD_SMAC_RESULT(mode) |
				      V_FW_VI_MAC_CMD_IDX(idx));
	memcpy(p->macaddr, addr, sizeof(p->macaddr));

	ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), &c);
	if (ret == 0) {
		ret = G_FW_VI_MAC_CMD_IDX(be16_to_cpu(p->valid_to_idx));
		if (ret >= max_mac_addr)
			ret = -ENOMEM;
		if (smt_idx) {
			if (adap->params.viid_smt_extn_support)
				*smt_idx = G_FW_VI_MAC_CMD_SMTID(be32_to_cpu(c.op_to_viid));
			else {
				if (chip_id(adap) <= CHELSIO_T5)
					*smt_idx = (viid & M_FW_VIID_VIN) << 1;
				else
					*smt_idx = viid & M_FW_VIID_VIN;
			}
		}
	}
	return ret;
}