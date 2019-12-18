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
struct TYPE_3__ {int status; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  TYPE_1__ SATA_FIS_REG_D2H_T ;

/* Variables and functions */
 int ATA_STATUS_REG_ERROR_BIT ; 
 int /*<<< orphan*/  SCI_FAILURE_IO_RESPONSE_VALID ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 

SCI_STATUS scic_sds_stp_packet_request_process_status_fis(
   SCIC_SDS_REQUEST_T * this_request,
   SATA_FIS_REG_D2H_T * status_fis
)
{
   SCI_STATUS status = SCI_SUCCESS;

   //TODO: Process the error status fis, retrieve sense data.
   if (status_fis->status & ATA_STATUS_REG_ERROR_BIT)
      status = SCI_FAILURE_IO_RESPONSE_VALID;

   return status;
}