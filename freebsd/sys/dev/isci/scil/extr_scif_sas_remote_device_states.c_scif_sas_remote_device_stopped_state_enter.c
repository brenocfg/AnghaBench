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
struct TYPE_11__ {scalar_t__ request_count; scalar_t__ destruct_when_stopped; int /*<<< orphan*/  parent; TYPE_4__* domain; TYPE_2__* state_handlers; int /*<<< orphan*/  operation_status; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; TYPE_3__* state_handlers; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* device_stop_complete_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* destruct_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STOPPED ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  scif_sas_remote_device_state_handler_table ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scif_sas_remote_device_stopped_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)object;

   SET_STATE_HANDLER(
      fw_device,
      scif_sas_remote_device_state_handler_table,
      SCI_BASE_REMOTE_DEVICE_STATE_STOPPED
   );

   // There should be no outstanding requests for this device in the
   // stopped state.
   ASSERT(fw_device->request_count == 0);

   // If we are entering the stopped state as a result of a destruct
   // request, then let's perform the actual destruct operation now.
   if (fw_device->destruct_when_stopped == TRUE)
      fw_device->operation_status
         = fw_device->state_handlers->parent.destruct_handler(
              &fw_device->parent
           );

   /// @todo What should we do if this call fails?
   fw_device->domain->state_handlers->device_stop_complete_handler(
      &fw_device->domain->parent, &fw_device->parent
   );
}