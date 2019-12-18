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
typedef  int /*<<< orphan*/  u8 ;
struct nvme_completion {int /*<<< orphan*/  status; } ;
struct mpr_softc {int dummy; } ;
struct mpr_command {scalar_t__ cm_sense; scalar_t__ cm_reply; } ;
struct TYPE_2__ {int /*<<< orphan*/  ErrorResponseCount; } ;
typedef  TYPE_1__ Mpi26NVMeEncapsulatedErrorReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_SCSI_STATUS_GOOD ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprsas_nvme_trans_status_code (int /*<<< orphan*/ ,struct mpr_command*) ; 

__attribute__((used)) static u8
mprsas_complete_nvme_unmap(struct mpr_softc *sc, struct mpr_command *cm)
{
	Mpi26NVMeEncapsulatedErrorReply_t *mpi_reply;
	struct nvme_completion *nvme_completion = NULL;
	u8 scsi_status = MPI2_SCSI_STATUS_GOOD;

	mpi_reply =(Mpi26NVMeEncapsulatedErrorReply_t *)cm->cm_reply;
	if (le16toh(mpi_reply->ErrorResponseCount)){
		nvme_completion = (struct nvme_completion *)cm->cm_sense;
		scsi_status = mprsas_nvme_trans_status_code(
		    nvme_completion->status, cm);
	}
	return scsi_status;
}