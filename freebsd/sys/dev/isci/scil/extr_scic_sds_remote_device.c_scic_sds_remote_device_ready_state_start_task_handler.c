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
struct TYPE_5__ {int /*<<< orphan*/  rnc; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ scic_sds_port_start_io (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_port (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_start_request (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ scic_sds_remote_node_context_start_task (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ scic_sds_request_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_device_ready_state_start_task_handler(
   SCI_BASE_REMOTE_DEVICE_T *device,
   SCI_BASE_REQUEST_T       *request
)
{
   SCI_STATUS result;
   SCIC_SDS_REMOTE_DEVICE_T *this_device  = (SCIC_SDS_REMOTE_DEVICE_T *)device;
   SCIC_SDS_REQUEST_T       *task_request = (SCIC_SDS_REQUEST_T       *)request;

   // See if the port is in a state where we can start the IO request
   result = scic_sds_port_start_io(
      scic_sds_remote_device_get_port(this_device), this_device, task_request);

   if (result == SCI_SUCCESS)
   {
      result = scic_sds_remote_node_context_start_task(
                  this_device->rnc, task_request
               );

      if (result == SCI_SUCCESS)
      {
         result = scic_sds_request_start(task_request);
      }

      scic_sds_remote_device_start_request(this_device, task_request, result);
   }

   return result;
}