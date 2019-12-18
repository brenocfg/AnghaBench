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
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
#define  RES_COUNTER 138 
#define  RES_CQ 137 
#define  RES_EQ 136 
#define  RES_FS_RULE 135 
#define  RES_MAC 134 
#define  RES_MPT 133 
#define  RES_MTT 132 
#define  RES_QP 131 
#define  RES_SRQ 130 
#define  RES_VLAN 129 
#define  RES_XRCD 128 

__attribute__((used)) static const char *resource_str(enum mlx4_resource rt)
{
	switch (rt) {
	case RES_QP: return "RES_QP";
	case RES_CQ: return "RES_CQ";
	case RES_SRQ: return "RES_SRQ";
	case RES_MPT: return "RES_MPT";
	case RES_MTT: return "RES_MTT";
	case RES_MAC: return  "RES_MAC";
	case RES_VLAN: return  "RES_VLAN";
	case RES_EQ: return "RES_EQ";
	case RES_COUNTER: return "RES_COUNTER";
	case RES_FS_RULE: return "RES_FS_RULE";
	case RES_XRCD: return "RES_XRCD";
	default: return "Unknown resource type !!!";
	};
}