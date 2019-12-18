#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; TYPE_2__* state_handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_3__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_remote_device_reset(
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device;
   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)remote_device;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_device),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_reset(0x%x) enter\n",
      remote_device
   ));

   return this_device->state_handlers->parent.reset_handler(&this_device->parent);
}