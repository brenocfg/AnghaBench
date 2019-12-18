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
struct fw_vi_rxmode_cmd {void* mtu_to_vlanexen; void* retval_len16; void* op_to_viid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_LEN16 (struct fw_vi_rxmode_cmd) ; 
 int /*<<< orphan*/  FW_VI_RXMODE_CMD ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_CMD_WRITE ; 
 int M_FW_VI_RXMODE_CMD_ALLMULTIEN ; 
 int M_FW_VI_RXMODE_CMD_BROADCASTEN ; 
 int M_FW_VI_RXMODE_CMD_MTU ; 
 int M_FW_VI_RXMODE_CMD_PROMISCEN ; 
 int M_FW_VI_RXMODE_CMD_VLANEXEN ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_VI_RXMODE_CMD_ALLMULTIEN (int) ; 
 int V_FW_VI_RXMODE_CMD_BROADCASTEN (int) ; 
 int V_FW_VI_RXMODE_CMD_MTU (int) ; 
 int V_FW_VI_RXMODE_CMD_PROMISCEN (int) ; 
 int V_FW_VI_RXMODE_CMD_VIID (unsigned int) ; 
 int V_FW_VI_RXMODE_CMD_VLANEXEN (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_vi_rxmode_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox_meat (struct adapter*,unsigned int,struct fw_vi_rxmode_cmd*,int,int /*<<< orphan*/ *,int) ; 

int t4_set_rxmode(struct adapter *adap, unsigned int mbox, unsigned int viid,
		  int mtu, int promisc, int all_multi, int bcast, int vlanex,
		  bool sleep_ok)
{
	struct fw_vi_rxmode_cmd c;

	/* convert to FW values */
	if (mtu < 0)
		mtu = M_FW_VI_RXMODE_CMD_MTU;
	if (promisc < 0)
		promisc = M_FW_VI_RXMODE_CMD_PROMISCEN;
	if (all_multi < 0)
		all_multi = M_FW_VI_RXMODE_CMD_ALLMULTIEN;
	if (bcast < 0)
		bcast = M_FW_VI_RXMODE_CMD_BROADCASTEN;
	if (vlanex < 0)
		vlanex = M_FW_VI_RXMODE_CMD_VLANEXEN;

	memset(&c, 0, sizeof(c));
	c.op_to_viid = cpu_to_be32(V_FW_CMD_OP(FW_VI_RXMODE_CMD) |
				   F_FW_CMD_REQUEST | F_FW_CMD_WRITE |
				   V_FW_VI_RXMODE_CMD_VIID(viid));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.mtu_to_vlanexen =
		cpu_to_be32(V_FW_VI_RXMODE_CMD_MTU(mtu) |
			    V_FW_VI_RXMODE_CMD_PROMISCEN(promisc) |
			    V_FW_VI_RXMODE_CMD_ALLMULTIEN(all_multi) |
			    V_FW_VI_RXMODE_CMD_BROADCASTEN(bcast) |
			    V_FW_VI_RXMODE_CMD_VLANEXEN(vlanex));
	return t4_wr_mbox_meat(adap, mbox, &c, sizeof(c), NULL, sleep_ok);
}