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
struct mps_softc {int dummy; } ;
struct mps_command {scalar_t__ cm_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  SGLOffset0; } ;
typedef  TYPE_1__ MPI2_SCSI_IO_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  mps_print_sgl (struct mps_softc*,struct mps_command*,int /*<<< orphan*/ ) ; 

void
mps_print_scsiio_cmd(struct mps_softc *sc, struct mps_command *cm)
{
	MPI2_SCSI_IO_REQUEST *req;

	req = (MPI2_SCSI_IO_REQUEST *)cm->cm_req;
	mps_print_sgl(sc, cm, req->SGLOffset0);
}