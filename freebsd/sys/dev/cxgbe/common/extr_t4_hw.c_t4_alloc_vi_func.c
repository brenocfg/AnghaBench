#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct fw_vi_cmd {unsigned int nmac; void* alloc_to_len16; int /*<<< orphan*/  norss_rsssize; int /*<<< orphan*/  nmac0; int /*<<< orphan*/  nmac1; int /*<<< orphan*/  nmac2; int /*<<< orphan*/  nmac3; int /*<<< orphan*/  mac; int /*<<< orphan*/  type_to_viid; int /*<<< orphan*/  portid_pkd; void* op_to_vfn; } ;
struct TYPE_2__ {scalar_t__ viid_smt_extn_support; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_LEN16 (struct fw_vi_cmd) ; 
 int /*<<< orphan*/  FW_VI_CMD ; 
 int F_FW_CMD_EXEC ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_CMD_WRITE ; 
 int F_FW_VI_CMD_ALLOC ; 
 int /*<<< orphan*/  F_FW_VI_CMD_NORSS ; 
 int /*<<< orphan*/  G_FW_VIID_VIN (int) ; 
 int /*<<< orphan*/  G_FW_VIID_VIVLD (int) ; 
 int /*<<< orphan*/  G_FW_VI_CMD_RSSSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_VI_CMD_VFVLD (int /*<<< orphan*/ ) ; 
 int G_FW_VI_CMD_VIID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_VI_CMD_VIN (int /*<<< orphan*/ ) ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_VI_CMD_FUNC (unsigned int) ; 
 int V_FW_VI_CMD_PFN (unsigned int) ; 
 int /*<<< orphan*/  V_FW_VI_CMD_PORTID (unsigned int) ; 
 int V_FW_VI_CMD_TYPE (unsigned int) ; 
 int V_FW_VI_CMD_VFN (unsigned int) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fw_vi_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_vi_cmd*,int,struct fw_vi_cmd*) ; 

int t4_alloc_vi_func(struct adapter *adap, unsigned int mbox,
		     unsigned int port, unsigned int pf, unsigned int vf,
		     unsigned int nmac, u8 *mac, u16 *rss_size,
		     uint8_t *vfvld, uint16_t *vin,
		     unsigned int portfunc, unsigned int idstype)
{
	int ret;
	struct fw_vi_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = cpu_to_be32(V_FW_CMD_OP(FW_VI_CMD) | F_FW_CMD_REQUEST |
				  F_FW_CMD_WRITE | F_FW_CMD_EXEC |
				  V_FW_VI_CMD_PFN(pf) | V_FW_VI_CMD_VFN(vf));
	c.alloc_to_len16 = cpu_to_be32(F_FW_VI_CMD_ALLOC | FW_LEN16(c));
	c.type_to_viid = cpu_to_be16(V_FW_VI_CMD_TYPE(idstype) |
				     V_FW_VI_CMD_FUNC(portfunc));
	c.portid_pkd = V_FW_VI_CMD_PORTID(port);
	c.nmac = nmac - 1;
	if(!rss_size)
		c.norss_rsssize = F_FW_VI_CMD_NORSS;

	ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), &c);
	if (ret)
		return ret;
	ret = G_FW_VI_CMD_VIID(be16_to_cpu(c.type_to_viid));

	if (mac) {
		memcpy(mac, c.mac, sizeof(c.mac));
		switch (nmac) {
		case 5:
			memcpy(mac + 24, c.nmac3, sizeof(c.nmac3));
		case 4:
			memcpy(mac + 18, c.nmac2, sizeof(c.nmac2));
		case 3:
			memcpy(mac + 12, c.nmac1, sizeof(c.nmac1));
		case 2:
			memcpy(mac + 6,  c.nmac0, sizeof(c.nmac0));
		}
	}
	if (rss_size)
		*rss_size = G_FW_VI_CMD_RSSSIZE(be16_to_cpu(c.norss_rsssize));
	if (vfvld) {
		*vfvld = adap->params.viid_smt_extn_support ?
		    G_FW_VI_CMD_VFVLD(be32_to_cpu(c.alloc_to_len16)) :
		    G_FW_VIID_VIVLD(ret);
	}
	if (vin) {
		*vin = adap->params.viid_smt_extn_support ?
		    G_FW_VI_CMD_VIN(be32_to_cpu(c.alloc_to_len16)) :
		    G_FW_VIID_VIN(ret);
	}

	return ret;
}