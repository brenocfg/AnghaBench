#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_22__ {int link_speed_active; int link_speed_enabled; } ;
struct TYPE_21__ {scalar_t__ link_width_active; scalar_t__ link_width_enabled; int capability_mask; } ;
struct TYPE_19__ {TYPE_5__ ext_port_info; TYPE_4__ port_info; } ;
typedef  TYPE_2__ osm_physp_t ;
struct TYPE_18__ {scalar_t__ node_type; int /*<<< orphan*/  node_guid; } ;
struct TYPE_20__ {int /*<<< orphan*/  print_desc; TYPE_1__ node_info; } ;
typedef  TYPE_3__ osm_node_t ;
typedef  TYPE_4__ ib_port_info_t ;
typedef  TYPE_5__ ib_mlnx_ext_port_info_t ;
struct TYPE_23__ {scalar_t__ node_type_lim; int /*<<< orphan*/  ports_unknown_width; int /*<<< orphan*/  unknown_width_ports; int /*<<< orphan*/  ports_2X; int /*<<< orphan*/  ports_12X; int /*<<< orphan*/  ports_8X; int /*<<< orphan*/  ports_4X; int /*<<< orphan*/  ports_1X; int /*<<< orphan*/  ports_unknown_speed; int /*<<< orphan*/  unknown_speed_ports; int /*<<< orphan*/  ports_edr; int /*<<< orphan*/  ports_fdr; int /*<<< orphan*/  ports_reduced_speed; int /*<<< orphan*/  reduced_speed_ports; int /*<<< orphan*/  ports_unenabled_speed; int /*<<< orphan*/  unenabled_speed_ports; int /*<<< orphan*/  ports_qdr; int /*<<< orphan*/  ports_fdr10; int /*<<< orphan*/  ports_ddr; int /*<<< orphan*/  ports_sdr; int /*<<< orphan*/  ports_reduced_width; int /*<<< orphan*/  reduced_width_ports; int /*<<< orphan*/  ports_unenabled_width; int /*<<< orphan*/  unenabled_width_ports; int /*<<< orphan*/  total_ports; int /*<<< orphan*/  ports_disabled; int /*<<< orphan*/  disabled_ports; int /*<<< orphan*/  ports_active; int /*<<< orphan*/  ports_down; int /*<<< orphan*/  total_nodes; } ;
typedef  TYPE_6__ fabric_stats_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;

/* Variables and functions */
 int FDR10 ; 
 scalar_t__ IB_LINK_ACTIVE ; 
 scalar_t__ IB_LINK_DOWN ; 
#define  IB_LINK_SPEED_ACTIVE_10 139 
#define  IB_LINK_SPEED_ACTIVE_2_5 138 
#define  IB_LINK_SPEED_ACTIVE_5 137 
#define  IB_LINK_SPEED_ACTIVE_EXTENDED 136 
#define  IB_LINK_SPEED_EXT_ACTIVE_14 135 
#define  IB_LINK_SPEED_EXT_ACTIVE_25 134 
#define  IB_LINK_SPEED_EXT_ACTIVE_NONE 133 
 scalar_t__ IB_LINK_SPEED_EXT_DISABLE ; 
#define  IB_LINK_WIDTH_ACTIVE_12X 132 
#define  IB_LINK_WIDTH_ACTIVE_1X 131 
#define  IB_LINK_WIDTH_ACTIVE_2X 130 
#define  IB_LINK_WIDTH_ACTIVE_4X 129 
#define  IB_LINK_WIDTH_ACTIVE_8X 128 
 scalar_t__ IB_NODE_TYPE_SWITCH ; 
 int IB_PORT_CAP_HAS_EXT_SPEEDS ; 
 scalar_t__ IB_PORT_PHYS_STATE_DISABLED ; 
 int /*<<< orphan*/  __tag_port_report (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_ntoh64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_port_info_get_link_speed_active (TYPE_4__*) ; 
 scalar_t__ ib_port_info_get_link_speed_enabled (TYPE_4__*) ; 
 scalar_t__ ib_port_info_get_link_speed_ext_active (TYPE_4__*) ; 
 scalar_t__ ib_port_info_get_link_speed_ext_enabled (TYPE_4__*) ; 
 scalar_t__ ib_port_info_get_link_speed_ext_sup (TYPE_4__*) ; 
 scalar_t__ ib_port_info_get_port_phys_state (TYPE_4__*) ; 
 scalar_t__ ib_port_info_get_port_state (TYPE_4__*) ; 
 scalar_t__ osm_node_get_num_physp (TYPE_3__*) ; 
 TYPE_2__* osm_node_get_physp_ptr (TYPE_3__*,scalar_t__) ; 
 scalar_t__ osm_node_get_type (TYPE_3__*) ; 

__attribute__((used)) static void __get_stats(cl_map_item_t * const p_map_item, void *context)
{
	fabric_stats_t *fs = (fabric_stats_t *) context;
	osm_node_t *node = (osm_node_t *) p_map_item;
	osm_physp_t *physp0;
	ib_port_info_t *pi0;
	uint8_t num_ports = osm_node_get_num_physp(node);
	uint8_t port = 0;

	/* Skip nodes we are not interested in */
	if (fs->node_type_lim != 0
	    && fs->node_type_lim != node->node_info.node_type)
		return;

	fs->total_nodes++;

	if (osm_node_get_type(node) == IB_NODE_TYPE_SWITCH) {
		physp0 = osm_node_get_physp_ptr(node, 0);
		pi0 = &physp0->port_info;
	} else
		pi0 = NULL;

	for (port = 1; port < num_ports; port++) {
		osm_physp_t *phys = osm_node_get_physp_ptr(node, port);
		ib_port_info_t *pi = NULL;
		ib_mlnx_ext_port_info_t *epi = NULL;
		uint8_t active_speed = 0;
		uint8_t enabled_speed = 0;
		uint8_t active_width = 0;
		uint8_t enabled_width = 0;
		uint8_t port_state = 0;
		uint8_t port_phys_state = 0;

		if (!phys)
			continue;

		pi = &phys->port_info;
		epi = &phys->ext_port_info;
		if (!pi0)
			pi0 = pi;
		active_speed = ib_port_info_get_link_speed_active(pi);
		enabled_speed = ib_port_info_get_link_speed_enabled(pi);
		active_width = pi->link_width_active;
		enabled_width = pi->link_width_enabled;
		port_state = ib_port_info_get_port_state(pi);
		port_phys_state = ib_port_info_get_port_phys_state(pi);

		if (port_state == IB_LINK_DOWN)
			fs->ports_down++;
		else if (port_state == IB_LINK_ACTIVE)
			fs->ports_active++;
		if (port_phys_state == IB_PORT_PHYS_STATE_DISABLED) {
			__tag_port_report(&(fs->disabled_ports),
					  cl_ntoh64(node->node_info.node_guid),
					  port, node->print_desc);
			fs->ports_disabled++;
		}

		fs->total_ports++;

		if (port_state == IB_LINK_DOWN)
			continue;

		if (!(active_width & enabled_width)) {
			__tag_port_report(&(fs->unenabled_width_ports),
					  cl_ntoh64(node->node_info.node_guid),
					  port, node->print_desc);
			fs->ports_unenabled_width++;
		}
		else if ((enabled_width ^ active_width) > active_width) {
			__tag_port_report(&(fs->reduced_width_ports),
					  cl_ntoh64(node->node_info.node_guid),
					  port, node->print_desc);
			fs->ports_reduced_width++;
		}

		/* unenabled speed usually due to problems with force_link_speed */
		if (!(active_speed & enabled_speed)) {
			__tag_port_report(&(fs->unenabled_speed_ports),
					  cl_ntoh64(node->node_info.node_guid),
					  port, node->print_desc);
			fs->ports_unenabled_speed++;
		}
		else if ((enabled_speed ^ active_speed) > active_speed) {
			__tag_port_report(&(fs->reduced_speed_ports),
					  cl_ntoh64(node->node_info.node_guid),
					  port, node->print_desc);
			fs->ports_reduced_speed++;
		}

		switch (active_speed) {
		case IB_LINK_SPEED_ACTIVE_2_5:
			fs->ports_sdr++;
			break;
		case IB_LINK_SPEED_ACTIVE_5:
			fs->ports_ddr++;
			break;
		case IB_LINK_SPEED_ACTIVE_10:
			if (!(pi0->capability_mask & IB_PORT_CAP_HAS_EXT_SPEEDS) ||
			    !ib_port_info_get_link_speed_ext_active(pi)) {
				if (epi->link_speed_active & FDR10)
					fs->ports_fdr10++;
				else {
					fs->ports_qdr++;
					/* check for speed reduced from FDR10 */
					if (epi->link_speed_enabled & FDR10) {
						__tag_port_report(&(fs->reduced_speed_ports),
								  cl_ntoh64(node->node_info.node_guid),
								  port, node->print_desc);
						fs->ports_reduced_speed++;
					}
				}
			}
			break;
		case IB_LINK_SPEED_ACTIVE_EXTENDED:
			break;
		default:
			__tag_port_report(&(fs->unknown_speed_ports),
					  cl_ntoh64(node->node_info.node_guid),
					  port, node->print_desc);
			fs->ports_unknown_speed++;
			break;
		}
		if (pi0->capability_mask & IB_PORT_CAP_HAS_EXT_SPEEDS &&
		    ib_port_info_get_link_speed_ext_sup(pi) &&
		    (enabled_speed = ib_port_info_get_link_speed_ext_enabled(pi)) != IB_LINK_SPEED_EXT_DISABLE &&
		    active_speed == IB_LINK_SPEED_ACTIVE_10) {
			active_speed = ib_port_info_get_link_speed_ext_active(pi);
			if (!(active_speed & enabled_speed)) {
				__tag_port_report(&(fs->unenabled_speed_ports),
						  cl_ntoh64(node->node_info.node_guid),
						  port, node->print_desc);
				fs->ports_unenabled_speed++;
			}
			else if ((enabled_speed ^ active_speed) > active_speed) {
				__tag_port_report(&(fs->reduced_speed_ports),
						  cl_ntoh64(node->node_info.node_guid),
						  port, node->print_desc);
				fs->ports_reduced_speed++;
			}
			switch (active_speed) {
			case IB_LINK_SPEED_EXT_ACTIVE_14:
				fs->ports_fdr++;
				break;
			case IB_LINK_SPEED_EXT_ACTIVE_25:
				fs->ports_edr++;
				break;
			case IB_LINK_SPEED_EXT_ACTIVE_NONE:
				break;
			default:
				__tag_port_report(&(fs->unknown_speed_ports),
						  cl_ntoh64(node->node_info.node_guid),
						  port, node->print_desc);
				fs->ports_unknown_speed++;
				break;
			}
		}
		switch (active_width) {
		case IB_LINK_WIDTH_ACTIVE_1X:
			fs->ports_1X++;
			break;
		case IB_LINK_WIDTH_ACTIVE_4X:
			fs->ports_4X++;
			break;
		case IB_LINK_WIDTH_ACTIVE_8X:
			fs->ports_8X++;
			break;
		case IB_LINK_WIDTH_ACTIVE_12X:
			fs->ports_12X++;
			break;
		case IB_LINK_WIDTH_ACTIVE_2X:
			fs->ports_2X++;
			break;
		default:
			__tag_port_report(&(fs->unknown_width_ports),
					  cl_ntoh64(node->node_info.node_guid),
					  port, node->print_desc);
			fs->ports_unknown_width++;
			break;
		}
	}
}