#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  parent; TYPE_4__* state_handlers; TYPE_2__* domain; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* destruct_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_3__ parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* device_destruct_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

SCI_STATUS scif_remote_device_destruct(
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE,
      "scif_remote_device_destruct(0x%x) enter\n",
      remote_device
   ));

   //remove the device from domain's remote_device_list
   fw_device->domain->state_handlers->device_destruct_handler(
      &fw_device->domain->parent, &fw_device->parent
   );

   // The destruct process may not complete immediately, since the core
   // remote device likely needs to be stopped first.  However, the user
   // is not given a callback notification for destruction.
   return fw_device->state_handlers->parent.destruct_handler(
             &fw_device->parent
          );
}