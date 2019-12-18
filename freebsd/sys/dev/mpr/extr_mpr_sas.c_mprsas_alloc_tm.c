#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mpr_softc {int dummy; } ;
struct mpr_command {scalar_t__ cm_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  Function; } ;
typedef  TYPE_1__ MPI2_SCSI_TASK_MANAGE_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_FUNCTION_SCSI_TASK_MGMT ; 
 int /*<<< orphan*/  MPR_FUNCTRACE (struct mpr_softc*) ; 
 struct mpr_command* mpr_alloc_high_priority_command (struct mpr_softc*) ; 

struct mpr_command *
mprsas_alloc_tm(struct mpr_softc *sc)
{
	MPI2_SCSI_TASK_MANAGE_REQUEST *req;
	struct mpr_command *tm;

	MPR_FUNCTRACE(sc);
	tm = mpr_alloc_high_priority_command(sc);
	if (tm == NULL)
		return (NULL);

	req = (MPI2_SCSI_TASK_MANAGE_REQUEST *)tm->cm_req;
	req->Function = MPI2_FUNCTION_SCSI_TASK_MGMT;
	return tm;
}