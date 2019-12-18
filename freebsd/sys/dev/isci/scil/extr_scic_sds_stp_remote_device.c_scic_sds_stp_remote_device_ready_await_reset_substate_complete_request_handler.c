#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  owning_port; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 scalar_t__ scic_sds_io_request_complete (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_sds_port_complete_io (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_device_decrement_request_count (TYPE_1__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_remote_device_ready_await_reset_substate_complete_request_handler(
   SCI_BASE_REMOTE_DEVICE_T * device,
   SCI_BASE_REQUEST_T       * request
)
{
   SCIC_SDS_REMOTE_DEVICE_T * this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;
   SCIC_SDS_REQUEST_T       * the_request = (SCIC_SDS_REQUEST_T *)request;
   SCI_STATUS                 status;

   status = scic_sds_io_request_complete(the_request);

   if (status == SCI_SUCCESS)
   {
      status = scic_sds_port_complete_io(
                  this_device->owning_port, this_device, the_request
               );

      if (status == SCI_SUCCESS)
         scic_sds_remote_device_decrement_request_count(this_device);
   }

   if (status != SCI_SUCCESS)
   {
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_device),
         SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
         "Port:0x%x Device:0x%x Request:0x%x Status:0x%x could not complete\n",
         this_device->owning_port, this_device, the_request, status
      ));
   }

   return status;
}