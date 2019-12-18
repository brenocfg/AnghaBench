#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  length; } ;
struct TYPE_11__ {TYPE_1__ A; } ;
struct TYPE_10__ {int /*<<< orphan*/  do_translate_sgl; } ;
struct TYPE_9__ {int /*<<< orphan*/  user_request; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;
typedef  TYPE_3__ SCIC_IO_SATA_PARAMETERS_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  scic_cb_io_request_do_copy_rx_frames (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_io_request_get_data_direction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_request_get_sat_protocol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_io_request_construct_sata (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* scic_sds_request_get_sgl_element_pair (TYPE_2__*,int /*<<< orphan*/ ) ; 

SCI_STATUS scic_io_request_construct_advanced_sata(
   SCI_IO_REQUEST_HANDLE_T     scic_io_request,
   SCIC_IO_SATA_PARAMETERS_T * io_parameters
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
               scic_sds_request_get_sgl_element_pair(request, 0)->A.length,
               scic_cb_io_request_get_data_direction(request->user_request),
               scic_cb_io_request_do_copy_rx_frames(request->user_request),
               io_parameters->do_translate_sgl
            );

   return status;
}