#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_5__ {int /*<<< orphan*/  is_vport; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_1__ ocs_sport_t ;
struct TYPE_6__ {scalar_t__ fc_id; } ;
typedef  TYPE_2__ ocs_fcport ;

/* Variables and functions */
 TYPE_2__* FCPORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ocs_scsi_ini_del_sport(ocs_sport_t *sport)
{
	ocs_t *ocs = sport->ocs;
	ocs_fcport *fcp = FCPORT(ocs, 0);

	if (!sport->is_vport) {
		fcp->fc_id = 0;	
	}
}