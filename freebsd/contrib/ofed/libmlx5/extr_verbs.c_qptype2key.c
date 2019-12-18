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
typedef  enum ibv_qp_type { ____Placeholder_ibv_qp_type } ibv_qp_type ;

/* Variables and functions */
#define  IBV_QPT_RAW_PACKET 131 
#define  IBV_QPT_RC 130 
#define  IBV_QPT_UC 129 
#define  IBV_QPT_UD 128 

__attribute__((used)) static const char *qptype2key(enum ibv_qp_type type)
{
	switch (type) {
	case IBV_QPT_RC: return "HUGE_RC";
	case IBV_QPT_UC: return "HUGE_UC";
	case IBV_QPT_UD: return "HUGE_UD";
	case IBV_QPT_RAW_PACKET: return "HUGE_RAW_ETH";
	default: return "HUGE_NA";
	}
}