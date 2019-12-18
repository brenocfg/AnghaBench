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
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SATI_DEVICE_STATE_STOPPED ; 
 int /*<<< orphan*/  SCSI_ASCQ_INITIALIZING_COMMAND_REQUIRED ; 
 int /*<<< orphan*/  SCSI_ASC_INITIALIZING_COMMAND_REQUIRED ; 
 int /*<<< orphan*/  SCSI_SENSE_NOT_READY ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL sati_device_state_stopped(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io
)
{
   if(sequence->device->state == SATI_DEVICE_STATE_STOPPED)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_NOT_READY ,
         SCSI_ASC_INITIALIZING_COMMAND_REQUIRED,
         SCSI_ASCQ_INITIALIZING_COMMAND_REQUIRED
      );
      return TRUE;
   }
   return FALSE;
}