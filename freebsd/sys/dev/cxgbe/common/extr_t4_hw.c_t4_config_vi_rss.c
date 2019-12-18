#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* secretkeyxor; void* secretkeyidx_pkd; void* defaultq_to_udpen; } ;
struct TYPE_4__ {TYPE_1__ basicvirtual; } ;
struct fw_rss_vi_config_cmd {TYPE_2__ u; void* retval_len16; void* op_to_viid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 unsigned int FW_LEN16 (struct fw_rss_vi_config_cmd) ; 
 int /*<<< orphan*/  FW_RSS_VI_CONFIG_CMD ; 
 unsigned int F_FW_CMD_REQUEST ; 
 unsigned int F_FW_CMD_WRITE ; 
 unsigned int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 unsigned int V_FW_RSS_VI_CONFIG_CMD_DEFAULTQ (unsigned int) ; 
 unsigned int V_FW_RSS_VI_CONFIG_CMD_SECRETKEYIDX (unsigned int) ; 
 unsigned int V_FW_RSS_VI_CONFIG_CMD_VIID (unsigned int) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_vi_config_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,int,struct fw_rss_vi_config_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_config_vi_rss(struct adapter *adapter, int mbox, unsigned int viid,
		     unsigned int flags, unsigned int defq, unsigned int skeyidx,
		     unsigned int skey)
{
	struct fw_rss_vi_config_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_viid = cpu_to_be32(V_FW_CMD_OP(FW_RSS_VI_CONFIG_CMD) |
				   F_FW_CMD_REQUEST | F_FW_CMD_WRITE |
				   V_FW_RSS_VI_CONFIG_CMD_VIID(viid));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.basicvirtual.defaultq_to_udpen = cpu_to_be32(flags |
					V_FW_RSS_VI_CONFIG_CMD_DEFAULTQ(defq));
	c.u.basicvirtual.secretkeyidx_pkd = cpu_to_be32(
					V_FW_RSS_VI_CONFIG_CMD_SECRETKEYIDX(skeyidx));
	c.u.basicvirtual.secretkeyxor = cpu_to_be32(skey);

	return t4_wr_mbox(adapter, mbox, &c, sizeof(c), NULL);
}