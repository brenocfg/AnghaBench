#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ scic_sds_port_complete_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_device_decrement_request_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_port (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_sds_request_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_device_resetting_state_complete_request_handler(
   SCI_BASE_REMOTE_DEVICE_T *device,
   SCI_BASE_REQUEST_T       *request
)
{
   SCI_STATUS status = SCI_SUCCESS;
   SCIC_SDS_REQUEST_T       *this_request = (SCIC_SDS_REQUEST_T   *)request;
   SCIC_SDS_REMOTE_DEVICE_T *this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;

   status = scic_sds_request_complete(this_request);

   if (status == SCI_SUCCESS)
   {
      status = scic_sds_port_complete_io(
         scic_sds_remote_device_get_port(this_device), this_device, this_request);

      if (status == SCI_SUCCESS)
      {
         scic_sds_remote_device_decrement_request_count(this_device);
      }
   }

   return status;
}