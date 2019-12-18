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
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;
struct ocs_lun_crn {scalar_t__ crnseed; } ;
struct TYPE_4__ {struct ocs_lun_crn** lun_crn; } ;
struct TYPE_5__ {TYPE_1__ ini_node; } ;
typedef  TYPE_2__ ocs_node_t ;

/* Variables and functions */
 size_t OCS_MAX_LUN ; 

void
ocs_reset_crn(ocs_node_t *node, uint64_t lun)
{
	uint32_t idx;
	struct ocs_lun_crn *lcrn = NULL;
	idx = lun % OCS_MAX_LUN;

	lcrn = node->ini_node.lun_crn[idx];
	if (lcrn)
		lcrn->crnseed = 0;

	return;
}