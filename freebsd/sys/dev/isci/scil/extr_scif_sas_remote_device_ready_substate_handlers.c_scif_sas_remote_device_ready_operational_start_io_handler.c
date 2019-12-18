#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_8__ {TYPE_2__ parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  request_count; } ;
struct TYPE_5__ {scalar_t__ (* start_handler ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_3__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_remote_device_ready_operational_start_io_handler(
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * io_request
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;
   SCIF_SAS_IO_REQUEST_T    * fw_io     = (SCIF_SAS_IO_REQUEST_T*) io_request;
   SCI_STATUS                 status;

   status = fw_io->parent.state_handlers->start_handler(&fw_io->parent.parent);

   if (status == SCI_SUCCESS)
   {
      fw_device->request_count++;
   }

   return status;
}