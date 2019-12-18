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
typedef  size_t uint32_t ;
struct ocs_lun_crn {int dummy; } ;
struct TYPE_4__ {struct ocs_lun_crn** lun_crn; } ;
struct TYPE_5__ {int /*<<< orphan*/  ocs; TYPE_1__ ini_node; } ;
typedef  TYPE_2__ ocs_node_t ;

/* Variables and functions */
 size_t OCS_MAX_LUN ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,struct ocs_lun_crn*,int) ; 

void
ocs_del_crn(ocs_node_t *node)
{
	uint32_t i;
	struct ocs_lun_crn *lcrn = NULL;
	
	for(i = 0; i < OCS_MAX_LUN; i++) {
		lcrn = node->ini_node.lun_crn[i];
		if (lcrn) {
			ocs_free(node->ocs, lcrn, sizeof(*lcrn));
		}
	}

	return;
}