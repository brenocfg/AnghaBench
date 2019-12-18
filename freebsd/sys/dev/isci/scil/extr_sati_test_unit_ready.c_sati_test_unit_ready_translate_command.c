#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_1__* device; } ;
struct TYPE_6__ {scalar_t__ state; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 scalar_t__ SATI_DEVICE_STATE_FORMAT_UNIT_IN_PROGRESS ; 
 scalar_t__ SATI_DEVICE_STATE_SELF_TEST_IN_PROGRESS ; 
 scalar_t__ SATI_DEVICE_STATE_STOPPED ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_TEST_UNIT_READY ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SCSI_ASCQ_INITIALIZING_COMMAND_REQUIRED ; 
 int /*<<< orphan*/  SCSI_ASCQ_LUN_FORMAT_IN_PROGRESS ; 
 int /*<<< orphan*/  SCSI_ASCQ_LUN_SELF_TEST_IN_PROGRESS ; 
 int /*<<< orphan*/  SCSI_ASC_INITIALIZING_COMMAND_REQUIRED ; 
 int /*<<< orphan*/  SCSI_ASC_LUN_FORMAT_IN_PROGRESS ; 
 int /*<<< orphan*/  SCSI_ASC_LUN_SELF_TEST_IN_PROGRESS ; 
 int /*<<< orphan*/  SCSI_SENSE_NOT_READY ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  sati_ata_check_power_mode_construct (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_test_unit_ready_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   /**
    * SAT dictates:
    * - the device should be in a state to receive commands
    * - a stopped device should cause sense data.
    * - a format unit in progresss should cause sense data.
    * - a self-test in progress should cause sense data.
    * - a device fault occurred on previous request should cause sense data.
    * - handling the removable media feature set isn't supported according to
    *   SAT specifications.
    */
   if (sequence->device->state == SATI_DEVICE_STATE_STOPPED)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_NOT_READY,
         SCSI_ASC_INITIALIZING_COMMAND_REQUIRED,
         SCSI_ASCQ_INITIALIZING_COMMAND_REQUIRED
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }
   else if (sequence->device->state
            == SATI_DEVICE_STATE_SELF_TEST_IN_PROGRESS)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_NOT_READY,
         SCSI_ASC_LUN_SELF_TEST_IN_PROGRESS,
         SCSI_ASCQ_LUN_SELF_TEST_IN_PROGRESS
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }
   else if (sequence->device->state
            == SATI_DEVICE_STATE_FORMAT_UNIT_IN_PROGRESS)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_NOT_READY,
         SCSI_ASC_LUN_FORMAT_IN_PROGRESS,
         SCSI_ASCQ_LUN_FORMAT_IN_PROGRESS
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   // The CDB is properly formed and the device is ready.
   sequence->type = SATI_SEQUENCE_TEST_UNIT_READY;

   sati_ata_check_power_mode_construct(ata_io, sequence);
   return SATI_SUCCESS;
}