#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; } ;
struct TYPE_10__ {scalar_t__ smid; } ;
struct TYPE_11__ {TYPE_3__ context; } ;
struct mrsas_mfi_cmd {TYPE_4__ cmd_id; } ;
struct TYPE_9__ {int RequestFlags; scalar_t__ SMID; } ;
struct TYPE_8__ {scalar_t__ Words; } ;
struct TYPE_12__ {TYPE_2__ SCSIIO; TYPE_1__ addr; } ;
typedef  TYPE_5__ MRSAS_REQUEST_DESCRIPTOR_UNION ;

/* Variables and functions */
 int MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO ; 
 int MRSAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrsas_build_mptmfi_passthru (struct mrsas_softc*,struct mrsas_mfi_cmd*) ; 
 TYPE_5__* mrsas_get_request_desc (struct mrsas_softc*,scalar_t__) ; 

MRSAS_REQUEST_DESCRIPTOR_UNION *
mrsas_build_mpt_cmd(struct mrsas_softc *sc, struct mrsas_mfi_cmd *cmd)
{
	MRSAS_REQUEST_DESCRIPTOR_UNION *req_desc;
	u_int16_t index;

	if (mrsas_build_mptmfi_passthru(sc, cmd)) {
		device_printf(sc->mrsas_dev, "Cannot build MPT-MFI passthru cmd.\n");
		return NULL;
	}
	index = cmd->cmd_id.context.smid;

	req_desc = mrsas_get_request_desc(sc, index - 1);
	if (!req_desc)
		return NULL;

	req_desc->addr.Words = 0;
	req_desc->SCSIIO.RequestFlags = (MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO << MRSAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);

	req_desc->SCSIIO.SMID = index;

	return (req_desc);
}