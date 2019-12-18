#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lun ;
typedef  int /*<<< orphan*/  U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_14__ {scalar_t__ command_buffer; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* scic_cb_ssp_passthru_get_task_attribute ) (TYPE_4__*) ;int /*<<< orphan*/  (* scic_cb_ssp_passthru_get_cdb ) (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* scic_cb_ssp_passthru_get_lun ) (TYPE_4__*,int /*<<< orphan*/ **) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  lun_number; } ;
struct TYPE_11__ {int /*<<< orphan*/  task_attribute; scalar_t__ task_priority; scalar_t__ enable_first_burst; int /*<<< orphan*/  cdb; scalar_t__ additional_cdb_length; scalar_t__ lun; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCI_SSP_COMMAND_IU_T ;
typedef  TYPE_2__ SCI_SINGLE_LEVEL_LUN_T ;
typedef  TYPE_3__ SCIC_SSP_PASSTHRU_REQUEST_CALLBACKS_T ;
typedef  TYPE_4__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scic_word_copy_with_swap (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_io_request_build_ssp_command_iu_pass_through(
   SCIC_SDS_REQUEST_T   *this_request,
   SCIC_SSP_PASSTHRU_REQUEST_CALLBACKS_T *ssp_passthru_cb
)
{
   SCI_SSP_COMMAND_IU_T *command_frame;
   U32  cdb_length = 0, additional_cdb_length = 0;
   U8 *cdb_buffer, *additional_cdb_buffer;
   U8 *scsi_lun;
   SCI_STATUS sci_status = SCI_SUCCESS;
   SCI_SINGLE_LEVEL_LUN_T lun;

   command_frame =
      (SCI_SSP_COMMAND_IU_T *)this_request->command_buffer;

   //get the lun
   ssp_passthru_cb->scic_cb_ssp_passthru_get_lun (
      this_request,
     &scsi_lun
   );
   memset(&lun, 0, sizeof(lun));
   lun.lun_number = *scsi_lun;
   scic_word_copy_with_swap(
       (U32 *)command_frame->lun,
       (U32 *)&lun,
       sizeof(lun));

   ((U32 *)command_frame)[2] = 0;

   ssp_passthru_cb->scic_cb_ssp_passthru_get_cdb(
      this_request,
     &cdb_length,
     &cdb_buffer,
     &additional_cdb_length,
     &additional_cdb_buffer
   );

   command_frame->additional_cdb_length = additional_cdb_length;

   // ----------- TODO
   ///todo: what to do with additional cdb length and buffer as the current command buffer is
   // 16 bytes in intel_sas.h
   // ??? see the SAS command IU
   if (additional_cdb_length > 0)
   {
     return SCI_FAILURE_INVALID_PARAMETER_VALUE;
   }

   /// @todo Is it ok to leave junk at the end of the cdb buffer?
   scic_word_copy_with_swap(
      (U32 *)(&command_frame->cdb),
      (U32 *)(cdb_buffer),
      (cdb_length + 3) / sizeof(U32)
   );

   /////-------- End fo TODO

   command_frame->enable_first_burst = 0;
   command_frame->task_priority = 0;  //todo: check with Richard ????

   //get the task attribute
   command_frame->task_attribute = ssp_passthru_cb->scic_cb_ssp_passthru_get_task_attribute (
                                      this_request
                             );

   return sci_status;
}