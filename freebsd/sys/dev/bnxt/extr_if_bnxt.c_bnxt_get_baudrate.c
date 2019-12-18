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
typedef  int /*<<< orphan*/  uint64_t ;
struct bnxt_link_info {int link_speed; } ;

/* Variables and functions */
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_100GB 138 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_100MB 137 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_10GB 136 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_10MB 135 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_1GB 134 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_20GB 133 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_25GB 132 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_2GB 131 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_2_5GB 130 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_40GB 129 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_50GB 128 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  IF_Mbps (int) ; 

__attribute__((used)) static uint64_t
bnxt_get_baudrate(struct bnxt_link_info *link)
{
	switch (link->link_speed) {
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_100MB:
		return IF_Mbps(100);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_1GB:
		return IF_Gbps(1);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_2GB:
		return IF_Gbps(2);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_2_5GB:
		return IF_Mbps(2500);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_10GB:
		return IF_Gbps(10);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_20GB:
		return IF_Gbps(20);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_25GB:
		return IF_Gbps(25);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_40GB:
		return IF_Gbps(40);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_50GB:
		return IF_Gbps(50);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_100GB:
		return IF_Gbps(100);
	case HWRM_PORT_PHY_QCFG_OUTPUT_LINK_SPEED_10MB:
		return IF_Mbps(10);
	}
	return IF_Gbps(100);
}