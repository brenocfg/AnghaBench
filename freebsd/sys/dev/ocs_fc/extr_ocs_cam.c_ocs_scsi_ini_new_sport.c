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
struct TYPE_5__ {int /*<<< orphan*/  fc_id; TYPE_2__* tgt_data; int /*<<< orphan*/  is_vport; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_1__ ocs_sport_t ;
struct TYPE_6__ {int /*<<< orphan*/  fc_id; } ;
typedef  TYPE_2__ ocs_fcport ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 TYPE_2__* FCPORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t
ocs_scsi_ini_new_sport(ocs_sport_t *sport)
{
	ocs_t *ocs = sport->ocs;
	ocs_fcport *fcp = FCPORT(ocs, 0);

	if (!sport->is_vport) {
		sport->tgt_data = fcp;
		fcp->fc_id = sport->fc_id;	
	}

	return 0;
}