#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lun ;
typedef  int U32 ;
struct TYPE_8__ {scalar_t__ command_buffer; } ;
struct TYPE_7__ {int lun_number; } ;
struct TYPE_6__ {int additional_cdb_length; int /*<<< orphan*/  task_attribute; int /*<<< orphan*/  task_priority; scalar_t__ enable_first_burst; int /*<<< orphan*/  cdb; scalar_t__ lun; } ;
typedef  TYPE_1__ SCI_SSP_COMMAND_IU_T ;
typedef  TYPE_2__ SCI_SINGLE_LEVEL_LUN_T ;
typedef  TYPE_3__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ scic_cb_ssp_io_request_get_cdb_address (void*) ; 
 int scic_cb_ssp_io_request_get_cdb_length (void*) ; 
 int /*<<< orphan*/  scic_cb_ssp_io_request_get_command_priority (void*) ; 
 int scic_cb_ssp_io_request_get_lun (void*) ; 
 int /*<<< orphan*/  scic_cb_ssp_io_request_get_task_attribute (void*) ; 
 void* scic_sds_request_get_user_request (TYPE_3__*) ; 
 int /*<<< orphan*/  scic_word_copy_with_swap (int*,int*,int) ; 

__attribute__((used)) static
void scic_sds_io_request_build_ssp_command_iu(
   SCIC_SDS_REQUEST_T   *this_request
)
{
   SCI_SINGLE_LEVEL_LUN_T lun;
   SCI_SSP_COMMAND_IU_T *command_frame;
   void                 *os_handle;
   U32  cdb_length;
   U32 *cdb_buffer;

   command_frame =
      (SCI_SSP_COMMAND_IU_T *)this_request->command_buffer;

   os_handle = scic_sds_request_get_user_request(this_request);

   ((U32 *)&lun)[0] = 0;
   ((U32 *)&lun)[1] = 0;
   lun.lun_number = scic_cb_ssp_io_request_get_lun(os_handle) &0xff;
   /// @todo Is it ok to leave junk at the end of the cdb buffer?
   scic_word_copy_with_swap(
       (U32 *)command_frame->lun,
       (U32 *)&lun,
       sizeof(lun));

   ((U32 *)command_frame)[2] = 0;

   cdb_length = scic_cb_ssp_io_request_get_cdb_length(os_handle);
   cdb_buffer = (U32 *)scic_cb_ssp_io_request_get_cdb_address(os_handle);

   if (cdb_length > 16)
   {
      command_frame->additional_cdb_length = cdb_length - 16;
   }

   /// @todo Is it ok to leave junk at the end of the cdb buffer?
   scic_word_copy_with_swap(
      (U32 *)(&command_frame->cdb),
      (U32 *)(cdb_buffer),
      (cdb_length + 3) / sizeof(U32)
   );

   command_frame->enable_first_burst = 0;
   command_frame->task_priority =
      scic_cb_ssp_io_request_get_command_priority(os_handle);
   command_frame->task_attribute =
      scic_cb_ssp_io_request_get_task_attribute(os_handle);
}