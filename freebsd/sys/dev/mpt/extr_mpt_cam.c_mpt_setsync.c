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
struct mpt_softc {TYPE_1__* mpt_dev_page1; } ;
struct TYPE_2__ {int RequestedParameters; } ;
typedef  TYPE_1__* PTR_CONFIG_PAGE_SCSI_DEVICE_1 ;

/* Variables and functions */
 int MPI_SCSIDEVPAGE1_RP_DT ; 
 int MPI_SCSIDEVPAGE1_RP_IU ; 
 int MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK ; 
 int MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK ; 
 int MPI_SCSIDEVPAGE1_RP_QAS ; 
 int MPI_SCSIDEVPAGE1_RP_SHIFT_MAX_SYNC_OFFSET ; 
 int MPI_SCSIDEVPAGE1_RP_SHIFT_MIN_SYNC_PERIOD ; 

__attribute__((used)) static void
mpt_setsync(struct mpt_softc *mpt, int tgt, int period, int offset)
{
	PTR_CONFIG_PAGE_SCSI_DEVICE_1 ptr;

	ptr = &mpt->mpt_dev_page1[tgt];
	ptr->RequestedParameters &= ~MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK;
	ptr->RequestedParameters &= ~MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK;
	ptr->RequestedParameters &= ~MPI_SCSIDEVPAGE1_RP_DT;
	ptr->RequestedParameters &= ~MPI_SCSIDEVPAGE1_RP_QAS;
	ptr->RequestedParameters &= ~MPI_SCSIDEVPAGE1_RP_IU;
	if (period == 0) {
		return;
	}
	ptr->RequestedParameters |=
	    period << MPI_SCSIDEVPAGE1_RP_SHIFT_MIN_SYNC_PERIOD;
	ptr->RequestedParameters |=
	    offset << MPI_SCSIDEVPAGE1_RP_SHIFT_MAX_SYNC_OFFSET;
	if (period < 0xa) {
		ptr->RequestedParameters |= MPI_SCSIDEVPAGE1_RP_DT;
	}
	if (period < 0x9) {
		ptr->RequestedParameters |= MPI_SCSIDEVPAGE1_RP_QAS;
		ptr->RequestedParameters |= MPI_SCSIDEVPAGE1_RP_IU;
	}
}