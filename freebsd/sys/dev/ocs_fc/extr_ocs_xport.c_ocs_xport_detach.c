#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* ocs; } ;
typedef  TYPE_2__ ocs_xport_t ;
struct TYPE_9__ {int /*<<< orphan*/  hw; TYPE_1__* xport; scalar_t__ enable_ini; scalar_t__ config_tgt; } ;
typedef  TYPE_3__ ocs_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  stats_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_hw_teardown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_ini_del_device (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_scsi_tgt_del_device (TYPE_3__*) ; 
 scalar_t__ ocs_timer_pending (int /*<<< orphan*/ *) ; 

int32_t
ocs_xport_detach(ocs_xport_t *xport)
{
	ocs_t *ocs = xport->ocs;

	/* free resources associated with target-server and initiator-client */
	if (ocs->config_tgt)
		ocs_scsi_tgt_del_device(ocs);

	if (ocs->enable_ini) {
		ocs_scsi_ini_del_device(ocs);

		/*Shutdown FC Statistics timer*/
		if (ocs_timer_pending(&ocs->xport->stats_timer))
			ocs_del_timer(&ocs->xport->stats_timer);
	}

	ocs_hw_teardown(&ocs->hw);

	return 0;
}