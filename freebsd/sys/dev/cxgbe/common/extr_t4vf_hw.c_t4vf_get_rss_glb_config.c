#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int synmapen; int syn4tupenipv6; int syn2tupenipv6; int syn4tupenipv4; int syn2tupenipv4; int ofdmapen; int tnlmapen; int tnlalllookup; int hashtoeplitz; } ;
struct TYPE_12__ {TYPE_5__ basicvirtual; } ;
struct rss_params {int mode; TYPE_6__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  synmapen_to_hashtoeplitz; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode_pkd; } ;
struct TYPE_10__ {TYPE_3__ basicvirtual; TYPE_2__ manual; } ;
struct fw_rss_glb_config_cmd {TYPE_4__ u; void* retval_len16; void* op_to_write; } ;
struct TYPE_7__ {struct rss_params rss; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int FW_LEN16 (struct fw_rss_glb_config_cmd) ; 
 int /*<<< orphan*/  FW_RSS_GLB_CONFIG_CMD ; 
#define  FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL 128 
 int FW_SUCCESS ; 
 int F_FW_CMD_READ ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ ; 
 int F_FW_RSS_GLB_CONFIG_CMD_OFDMAPEN ; 
 int F_FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4 ; 
 int F_FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6 ; 
 int F_FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4 ; 
 int F_FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6 ; 
 int F_FW_RSS_GLB_CONFIG_CMD_SYNMAPEN ; 
 int F_FW_RSS_GLB_CONFIG_CMD_TNLALLLKP ; 
 int F_FW_RSS_GLB_CONFIG_CMD_TNLMAPEN ; 
 int G_FW_RSS_GLB_CONFIG_CMD_MODE (int) ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_rss_glb_config_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_rss_glb_config_cmd*,int,struct fw_rss_glb_config_cmd*) ; 

int t4vf_get_rss_glb_config(struct adapter *adapter)
{
	struct rss_params *rss = &adapter->params.rss;
	struct fw_rss_glb_config_cmd cmd, rpl;
	int v;

	/*
	 * Execute an RSS Global Configuration read command to retrieve
	 * our RSS configuration.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_write = cpu_to_be32(V_FW_CMD_OP(FW_RSS_GLB_CONFIG_CMD) |
				      F_FW_CMD_REQUEST |
				      F_FW_CMD_READ);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), &rpl);
	if (v != FW_SUCCESS)
		return v;

	/*
	 * Transate the big-endian RSS Global Configuration into our
	 * cpu-endian format based on the RSS mode.  We also do first level
	 * filtering at this point to weed out modes which don't support
	 * VF Drivers ...
	 */
	rss->mode = G_FW_RSS_GLB_CONFIG_CMD_MODE(
			be32_to_cpu(rpl.u.manual.mode_pkd));
	switch (rss->mode) {
	case FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL: {
		u32 word = be32_to_cpu(
				rpl.u.basicvirtual.synmapen_to_hashtoeplitz);

		rss->u.basicvirtual.synmapen =
			((word & F_FW_RSS_GLB_CONFIG_CMD_SYNMAPEN) != 0);
		rss->u.basicvirtual.syn4tupenipv6 =
			((word & F_FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV6) != 0);
		rss->u.basicvirtual.syn2tupenipv6 =
			((word & F_FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV6) != 0);
		rss->u.basicvirtual.syn4tupenipv4 =
			((word & F_FW_RSS_GLB_CONFIG_CMD_SYN4TUPENIPV4) != 0);
		rss->u.basicvirtual.syn2tupenipv4 =
			((word & F_FW_RSS_GLB_CONFIG_CMD_SYN2TUPENIPV4) != 0);

		rss->u.basicvirtual.ofdmapen =
			((word & F_FW_RSS_GLB_CONFIG_CMD_OFDMAPEN) != 0);

		rss->u.basicvirtual.tnlmapen =
			((word & F_FW_RSS_GLB_CONFIG_CMD_TNLMAPEN) != 0);
		rss->u.basicvirtual.tnlalllookup =
			((word  & F_FW_RSS_GLB_CONFIG_CMD_TNLALLLKP) != 0);

		rss->u.basicvirtual.hashtoeplitz =
			((word & F_FW_RSS_GLB_CONFIG_CMD_HASHTOEPLITZ) != 0);

		/* we need at least Tunnel Map Enable to be set */
		if (!rss->u.basicvirtual.tnlmapen)
			return -EINVAL;
		break;
	}

	default:
		/* all unknown/unsupported RSS modes result in an error */
		return -EINVAL;
	}

	return 0;
}