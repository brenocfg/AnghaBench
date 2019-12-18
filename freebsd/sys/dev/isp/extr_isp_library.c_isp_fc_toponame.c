#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ isp_loopstate; int isp_topo; } ;
typedef  TYPE_1__ fcparam ;

/* Variables and functions */
 scalar_t__ LOOP_HAVE_ADDR ; 
#define  TOPO_FL_PORT 132 
#define  TOPO_F_PORT 131 
#define  TOPO_NL_PORT 130 
#define  TOPO_N_PORT 129 
#define  TOPO_PTP_STUB 128 

const char *
isp_fc_toponame(fcparam *fcp)
{

	if (fcp->isp_loopstate < LOOP_HAVE_ADDR) {
		return "Unavailable";
	}
	switch (fcp->isp_topo) {
	case TOPO_NL_PORT:      return "Private Loop (NL_Port)";
	case TOPO_FL_PORT:      return "Public Loop (FL_Port)";
	case TOPO_N_PORT:       return "Point-to-Point (N_Port)";
	case TOPO_F_PORT:       return "Fabric (F_Port)";
	case TOPO_PTP_STUB:     return "Point-to-Point (no response)";
	default:                return "?????";
	}
}