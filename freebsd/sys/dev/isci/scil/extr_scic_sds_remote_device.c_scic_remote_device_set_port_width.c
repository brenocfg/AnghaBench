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
typedef  scalar_t__ U8 ;
struct TYPE_3__ {scalar_t__ device_port_width; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 

SCI_STATUS scic_remote_device_set_port_width(
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device,
   U8                          new_port_width
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device;

   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)remote_device;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_device),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_set_port_width(0x%x, 0x%x) enter\n",
      remote_device, new_port_width
   ));

   if(new_port_width != 0)
   {
      this_device->device_port_width = new_port_width;

      return SCI_SUCCESS;
   }
   else
      return SCI_FAILURE;
}