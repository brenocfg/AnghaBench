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
struct TYPE_3__ {int /*<<< orphan*/  user_request; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  scic_cb_io_request_do_copy_rx_frames (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_io_request_get_data_direction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_io_request_get_transfer_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_request_get_sat_protocol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_io_request_construct_sata (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SCI_STATUS scic_io_request_construct_basic_sata(
   SCI_IO_REQUEST_HANDLE_T  scic_io_request
)
{
   SCI_STATUS           status;
   SCIC_SDS_REQUEST_T * request = (SCIC_SDS_REQUEST_T *)scic_io_request;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(scic_io_request),
      SCIC_LOG_OBJECT_STP_IO_REQUEST,
      "scic_io_request_construct_basic_sata(0x%x) enter\n",
      scic_io_request
   ));

   status = scic_sds_io_request_construct_sata(
               request,
               scic_cb_request_get_sat_protocol(request->user_request),
               scic_cb_io_request_get_transfer_length(request->user_request),
               scic_cb_io_request_get_data_direction(request->user_request),
               scic_cb_io_request_do_copy_rx_frames(request->user_request),
               TRUE
            );

   return status;
}