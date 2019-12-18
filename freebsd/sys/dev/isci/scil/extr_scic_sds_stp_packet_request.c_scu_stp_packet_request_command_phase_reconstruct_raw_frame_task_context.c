#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct STP_TASK_CONTEXT {int dummy; } ;
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_10__ {int /*<<< orphan*/  fis_type; } ;
struct TYPE_9__ {TYPE_6__* command_buffer; int /*<<< orphan*/  user_request; } ;
struct TYPE_7__ {TYPE_6__ stp; } ;
struct TYPE_8__ {int transfer_length_bytes; TYPE_1__ type; } ;
typedef  TYPE_2__ SCU_TASK_CONTEXT_T ;
typedef  TYPE_3__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SATA_FIS_REG_H2D_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATA_FIS_TYPE_DATA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 void* scic_cb_stp_packet_io_request_get_cdb_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_stp_packet_io_request_get_cdb_length (int /*<<< orphan*/ ) ; 

void scu_stp_packet_request_command_phase_reconstruct_raw_frame_task_context(
   SCIC_SDS_REQUEST_T * this_request,
   SCU_TASK_CONTEXT_T * task_context
)
{
   void * atapi_cdb =
      scic_cb_stp_packet_io_request_get_cdb_address(this_request->user_request);

   U32 atapi_cdb_length =
      scic_cb_stp_packet_io_request_get_cdb_length(this_request->user_request);

   memset(this_request->command_buffer, 0, sizeof(SATA_FIS_REG_H2D_T));
   memcpy( ((U8 *)this_request->command_buffer+sizeof(U32)), atapi_cdb, atapi_cdb_length);

   memset(&(task_context->type.stp), 0, sizeof(struct STP_TASK_CONTEXT));
   task_context->type.stp.fis_type = SATA_FIS_TYPE_DATA;

   //Note the data send out has to be 4 bytes aligned. Or else out hardware will
   //patch non-zero bytes and cause the target device unhappy.
   task_context->transfer_length_bytes = 12;
}