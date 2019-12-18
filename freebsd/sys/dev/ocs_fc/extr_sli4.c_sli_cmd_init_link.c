#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int topology; } ;
struct TYPE_11__ {TYPE_2__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_4__ sli4_t ;
struct TYPE_10__ {void* select_hightest_al_pa; void* skip_lisa; void* gen_loop_validity_check; void* skip_lirp_lilp; void* unfair; int /*<<< orphan*/  topology; void* enable_topology_failover; void* fixed_speed; void* loopback; } ;
struct TYPE_8__ {int /*<<< orphan*/  command; } ;
struct TYPE_12__ {int link_speed_selection_code; TYPE_3__ link_flags; int /*<<< orphan*/  selective_reset_al_pa; TYPE_1__ hdr; } ;
typedef  TYPE_5__ sli4_cmd_init_link_t ;
typedef  int int32_t ;

/* Variables and functions */
 void* FALSE ; 
#define  FC_LINK_SPEED_10G 137 
#define  FC_LINK_SPEED_16G 136 
#define  FC_LINK_SPEED_1G 135 
#define  FC_LINK_SPEED_2G 134 
#define  FC_LINK_SPEED_32G 133 
#define  FC_LINK_SPEED_4G 132 
#define  FC_LINK_SPEED_8G 131 
 int /*<<< orphan*/  FC_TOPOLOGY_P2P ; 
 int /*<<< orphan*/  SLI4_ASIC_TYPE_LANCER ; 
 int /*<<< orphan*/  SLI4_INIT_LINK_F_FCAL_FAIL_OVER ; 
 int /*<<< orphan*/  SLI4_INIT_LINK_F_FCAL_ONLY ; 
 int /*<<< orphan*/  SLI4_INIT_LINK_F_P2P_FAIL_OVER ; 
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_INIT_LINK ; 
#define  SLI4_READ_CFG_TOPO_FC 130 
 int SLI4_READ_CFG_TOPO_FCOE ; 
#define  SLI4_READ_CFG_TOPO_FC_AL 129 
#define  SLI4_READ_CFG_TOPO_FC_DA 128 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sli_get_asic_type (TYPE_4__*) ; 

int32_t
sli_cmd_init_link(sli4_t *sli4, void *buf, size_t size, uint32_t speed, uint8_t reset_alpa)
{
	sli4_cmd_init_link_t	*init_link = buf;

	ocs_memset(buf, 0, size);

	init_link->hdr.command = SLI4_MBOX_COMMAND_INIT_LINK;

	/* Most fields only have meaning for FC links */
	if (sli4->config.topology != SLI4_READ_CFG_TOPO_FCOE) {
		init_link->selective_reset_al_pa = reset_alpa;
		init_link->link_flags.loopback = FALSE;

		init_link->link_speed_selection_code = speed;
		switch (speed) {
		case FC_LINK_SPEED_1G:
		case FC_LINK_SPEED_2G:
		case FC_LINK_SPEED_4G:
		case FC_LINK_SPEED_8G:
		case FC_LINK_SPEED_16G:
		case FC_LINK_SPEED_32G:
			init_link->link_flags.fixed_speed = TRUE;
			break;
		case FC_LINK_SPEED_10G:
			ocs_log_test(sli4->os, "unsupported FC speed %d\n", speed);
			return 0;
		}

		switch (sli4->config.topology) {
		case SLI4_READ_CFG_TOPO_FC:
			/* Attempt P2P but failover to FC-AL */
			init_link->link_flags.enable_topology_failover = TRUE;

			if (sli_get_asic_type(sli4) == SLI4_ASIC_TYPE_LANCER)
				init_link->link_flags.topology = SLI4_INIT_LINK_F_FCAL_FAIL_OVER;
			else
				init_link->link_flags.topology = SLI4_INIT_LINK_F_P2P_FAIL_OVER;

			break;
		case SLI4_READ_CFG_TOPO_FC_AL:
			init_link->link_flags.topology = SLI4_INIT_LINK_F_FCAL_ONLY;
			if ((init_link->link_speed_selection_code == FC_LINK_SPEED_16G) ||
			    (init_link->link_speed_selection_code == FC_LINK_SPEED_32G)) {
				ocs_log_test(sli4->os, "unsupported FC-AL speed %d\n", speed);
				return 0;
			}
			break;
		case SLI4_READ_CFG_TOPO_FC_DA:
			init_link->link_flags.topology = FC_TOPOLOGY_P2P;
			break;
		default:
			ocs_log_test(sli4->os, "unsupported topology %#x\n", sli4->config.topology);
			return 0;
		}

		init_link->link_flags.unfair = FALSE;
		init_link->link_flags.skip_lirp_lilp = FALSE;
		init_link->link_flags.gen_loop_validity_check = FALSE;
		init_link->link_flags.skip_lisa = FALSE;
		init_link->link_flags.select_hightest_al_pa = FALSE;
	}

	return sizeof(sli4_cmd_init_link_t);
}