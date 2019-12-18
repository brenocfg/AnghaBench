#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ containing_device; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/ * SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 

SCI_STATUS scif_remote_device_get_containing_device(
   SCI_REMOTE_DEVICE_HANDLE_T          remote_device,
   SCI_REMOTE_DEVICE_HANDLE_T        * containing_device
)
{
   SCI_STATUS                 status      = SCI_FAILURE;
   SCIF_SAS_REMOTE_DEVICE_T * this_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                                            remote_device;

   if ( (this_device != NULL) && (containing_device != NULL) )
   {
      *containing_device = (SCI_REMOTE_DEVICE_HANDLE_T)(this_device->containing_device);
      if (*containing_device != NULL)
      {
         status = SCI_SUCCESS;
      }
   }

   return status;
}