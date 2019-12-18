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
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_3__ {int /*<<< orphan*/  tgt_data; int /*<<< orphan*/  is_vport; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_1__ ocs_sport_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FCPORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t
ocs_scsi_tgt_new_sport(ocs_sport_t *sport)
{
	ocs_t *ocs = sport->ocs;

	if(!sport->is_vport) {
		sport->tgt_data = FCPORT(ocs, 0);
	}

	return 0;
}