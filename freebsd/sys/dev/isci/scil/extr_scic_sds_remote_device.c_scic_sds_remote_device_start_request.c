#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* state_handlers; } ;
struct TYPE_8__ {TYPE_3__* owning_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* complete_io_handler ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  TYPE_2__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_sds_remote_device_increment_request_count (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

void scic_sds_remote_device_start_request(
   SCIC_SDS_REMOTE_DEVICE_T * this_device,
   SCIC_SDS_REQUEST_T       * the_request,
   SCI_STATUS                 status
)
{
   // We still have a fault in starting the io complete it on the port
   if (status == SCI_SUCCESS)
      scic_sds_remote_device_increment_request_count(this_device);
   else
   {
      this_device->owning_port->state_handlers->complete_io_handler(
         this_device->owning_port, this_device, the_request
      );
   }
}