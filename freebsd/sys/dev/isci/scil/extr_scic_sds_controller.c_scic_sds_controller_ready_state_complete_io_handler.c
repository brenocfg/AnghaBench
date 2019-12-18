#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U16 ;
struct TYPE_6__ {int /*<<< orphan*/ * io_request_table; } ;
struct TYPE_5__ {int /*<<< orphan*/  io_tag; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_INVALID_HANDLE ; 
 scalar_t__ SCI_SUCCESS ; 
 size_t scic_sds_io_tag_get_index (int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_remote_device_complete_io (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_ready_state_complete_io_handler(
   SCI_BASE_CONTROLLER_T    *controller,
   SCI_BASE_REMOTE_DEVICE_T *remote_device,
   SCI_BASE_REQUEST_T       *io_request
)
{
   U16        index;
   SCI_STATUS status;
   SCIC_SDS_CONTROLLER_T    *this_controller;
   SCIC_SDS_REQUEST_T       *the_request;
   SCIC_SDS_REMOTE_DEVICE_T *the_device;

   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;
   the_request = (SCIC_SDS_REQUEST_T *)io_request;
   the_device = (SCIC_SDS_REMOTE_DEVICE_T *)remote_device;

   status = scic_sds_remote_device_complete_io(
                  this_controller, the_device, the_request);

   if (status == SCI_SUCCESS)
   {
      index = scic_sds_io_tag_get_index(the_request->io_tag);
      this_controller->io_request_table[index] = SCI_INVALID_HANDLE;
   }

   return status;
}