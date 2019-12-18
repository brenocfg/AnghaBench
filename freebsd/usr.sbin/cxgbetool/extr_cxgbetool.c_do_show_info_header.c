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
typedef  int uint32_t ;

/* Variables and functions */
#define  T4_FILTER_ETH_TYPE 137 
#define  T4_FILTER_FCoE 136 
 int T4_FILTER_IC_VNIC ; 
#define  T4_FILTER_IP_FRAGMENT 135 
#define  T4_FILTER_IP_PROTO 134 
#define  T4_FILTER_IP_TOS 133 
#define  T4_FILTER_MAC_IDX 132 
#define  T4_FILTER_MPS_HIT_TYPE 131 
#define  T4_FILTER_PORT 130 
#define  T4_FILTER_VLAN 129 
#define  T4_FILTER_VNIC 128 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
do_show_info_header(uint32_t mode)
{
	uint32_t i;

	printf("%4s %8s", "Idx", "Hits");
	for (i = T4_FILTER_FCoE; i <= T4_FILTER_IP_FRAGMENT; i <<= 1) {
		switch (mode & i) {
		case T4_FILTER_FCoE:
			printf(" FCoE");
			break;

		case T4_FILTER_PORT:
			printf(" Port");
			break;

		case T4_FILTER_VNIC:
			if (mode & T4_FILTER_IC_VNIC)
				printf("   VFvld:PF:VF");
			else
				printf("     vld:oVLAN");
			break;

		case T4_FILTER_VLAN:
			printf("      vld:VLAN");
			break;

		case T4_FILTER_IP_TOS:
			printf("   TOS");
			break;

		case T4_FILTER_IP_PROTO:
			printf("  Prot");
			break;

		case T4_FILTER_ETH_TYPE:
			printf("   EthType");
			break;

		case T4_FILTER_MAC_IDX:
			printf("  MACIdx");
			break;

		case T4_FILTER_MPS_HIT_TYPE:
			printf(" MPS");
			break;

		case T4_FILTER_IP_FRAGMENT:
			printf(" Frag");
			break;

		default:
			/* compressed filter field not enabled */
			break;
		}
	}
	printf(" %20s %20s %9s %9s %s\n",
	    "DIP", "SIP", "DPORT", "SPORT", "Action");
}