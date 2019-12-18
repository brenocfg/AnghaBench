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
typedef  int uint32_t ;
struct TYPE_4__ {int topology; } ;
struct TYPE_5__ {int /*<<< orphan*/  os; TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  SLI4_READ_CFG_TOPO_FC 131 
#define  SLI4_READ_CFG_TOPO_FCOE 130 
#define  SLI4_READ_CFG_TOPO_FC_AL 129 
#define  SLI4_READ_CFG_TOPO_FC_DA 128 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int32_t
sli_set_topology(sli4_t *sli4, uint32_t value)
{
	int32_t	rc = 0;

	switch (value) {
	case SLI4_READ_CFG_TOPO_FCOE:
	case SLI4_READ_CFG_TOPO_FC:
	case SLI4_READ_CFG_TOPO_FC_DA:
	case SLI4_READ_CFG_TOPO_FC_AL:
		sli4->config.topology = value;
		break;
	default:
		ocs_log_test(sli4->os, "unsupported topology %#x\n", value);
		rc = -1;
	}

	return rc;
}