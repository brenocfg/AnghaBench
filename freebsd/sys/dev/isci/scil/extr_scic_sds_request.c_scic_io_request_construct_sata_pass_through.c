#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_12__ {int /*<<< orphan*/  protocol; scalar_t__ command_buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* scic_cb_passthru_get_data_direction ) (TYPE_3__*) ;int /*<<< orphan*/  (* scic_cb_passthru_get_transfer_length ) (TYPE_3__*) ;} ;
struct TYPE_11__ {TYPE_1__ common_callbacks; int /*<<< orphan*/  (* scic_cb_stp_passthru_get_protocol ) (TYPE_3__*) ;int /*<<< orphan*/  (* scic_cb_stp_passthru_get_register_fis ) (TYPE_3__*,int /*<<< orphan*/ **) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_IO_REQUEST_DATA_DIRECTION ;
typedef  TYPE_2__ SCIC_STP_PASSTHRU_REQUEST_CALLBACKS_T ;
typedef  TYPE_3__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SATA_FIS_REG_H2D_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_STP_PROTOCOL ; 
 scalar_t__ SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 scalar_t__ scic_sds_io_request_construct_sata (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 

SCI_STATUS scic_io_request_construct_sata_pass_through(
   SCI_IO_REQUEST_HANDLE_T scic_io_request,
   SCIC_STP_PASSTHRU_REQUEST_CALLBACKS_T *passthru_cb
)
{
   SCI_STATUS                       status = SCI_SUCCESS;
   SCIC_SDS_REQUEST_T               * this_request;
   U8                               sat_protocol;
   U8                               * reg_fis;
   U32                              transfer_length;
   SCI_IO_REQUEST_DATA_DIRECTION    data_direction;

   this_request = (SCIC_SDS_REQUEST_T * )scic_io_request;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(scic_io_request),
      SCIC_LOG_OBJECT_STP_IO_REQUEST,
      "scic_io_request_construct_sata_pass_through(0x%x) enter\n",
      scic_io_request
   ));

   passthru_cb->scic_cb_stp_passthru_get_register_fis(this_request, &reg_fis);

   if (reg_fis == NULL)
   {
      status = SCI_FAILURE_INVALID_PARAMETER_VALUE;
   }

   if (status == SCI_SUCCESS)
   {
      //copy the H2D Reg fis blindly from the request to the SCU command buffer
      memcpy ((U8 *)this_request->command_buffer, (U8 *)reg_fis, sizeof(SATA_FIS_REG_H2D_T));

      //continue to create the request
      sat_protocol = passthru_cb->scic_cb_stp_passthru_get_protocol(this_request);
      transfer_length = passthru_cb->common_callbacks.scic_cb_passthru_get_transfer_length(this_request);
      data_direction = passthru_cb->common_callbacks.scic_cb_passthru_get_data_direction(this_request);

      status = scic_sds_io_request_construct_sata(
                  this_request,
                  sat_protocol,
                  transfer_length,
                  data_direction,
                  TRUE,
                  TRUE
               );

      this_request->protocol = SCIC_STP_PROTOCOL;
   }

   return status;
}