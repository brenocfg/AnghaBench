#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int topology; } ;
struct TYPE_5__ {TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_link_medium_e ;

/* Variables and functions */
#define  SLI4_READ_CFG_TOPO_FC 131 
#define  SLI4_READ_CFG_TOPO_FCOE 130 
#define  SLI4_READ_CFG_TOPO_FC_AL 129 
#define  SLI4_READ_CFG_TOPO_FC_DA 128 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_ETHERNET ; 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_FC ; 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_MAX ; 

__attribute__((used)) static inline sli4_link_medium_e
sli_get_medium(sli4_t *sli4)
{
	switch (sli4->config.topology) {
	case SLI4_READ_CFG_TOPO_FCOE:
		return SLI_LINK_MEDIUM_ETHERNET;
	case SLI4_READ_CFG_TOPO_FC:
	case SLI4_READ_CFG_TOPO_FC_DA:
	case SLI4_READ_CFG_TOPO_FC_AL:
		return SLI_LINK_MEDIUM_FC;
	default:
		return SLI_LINK_MEDIUM_MAX;
	}
}