#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fcs_err; int /*<<< orphan*/  ucast_tx_pkts; int /*<<< orphan*/  ucast_rx_pkts; } ;
union ecore_mcp_protocol_stats {TYPE_2__ lan_stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_ucast_pkts; int /*<<< orphan*/  rx_ucast_pkts; } ;
struct ecore_eth_stats {TYPE_1__ common; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  err_get_proto_invalid_type; } ;
typedef  TYPE_3__ qlnx_host_t ;
typedef  enum ecore_mcp_protocol_type { ____Placeholder_ecore_mcp_protocol_type } ecore_mcp_protocol_type ;

/* Variables and functions */
#define  ECORE_MCP_LAN_STATS 128 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  ecore_get_vport_stats (struct ecore_dev*,struct ecore_eth_stats*) ; 

void
qlnx_get_protocol_stats(void *cdev, int proto_type, void *proto_stats)
{
	enum ecore_mcp_protocol_type	type;
	union ecore_mcp_protocol_stats	*stats;
	struct ecore_eth_stats		eth_stats;
	qlnx_host_t			*ha;

	ha = cdev;
	stats = proto_stats;
	type = proto_type;

        switch (type) {

        case ECORE_MCP_LAN_STATS:
                ecore_get_vport_stats((struct ecore_dev *)cdev, &eth_stats);
                stats->lan_stats.ucast_rx_pkts = eth_stats.common.rx_ucast_pkts;
                stats->lan_stats.ucast_tx_pkts = eth_stats.common.tx_ucast_pkts;
                stats->lan_stats.fcs_err = -1;
                break;

	default:
		ha->err_get_proto_invalid_type++;

		QL_DPRINT1(ha, "invalid protocol type 0x%x\n", type);
		break;
	}
	return;
}