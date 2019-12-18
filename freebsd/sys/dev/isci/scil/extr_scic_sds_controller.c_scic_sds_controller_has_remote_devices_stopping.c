#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_9__ {size_t remote_node_entries; TYPE_3__** device_table; } ;
struct TYPE_6__ {scalar_t__ current_state_id; } ;
struct TYPE_7__ {TYPE_1__ state_machine; } ;
struct TYPE_8__ {TYPE_2__ parent; } ;
typedef  TYPE_4__ SCIC_SDS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCI_BASE_REMOTE_DEVICE_STATE_STOPPING ; 
 int /*<<< orphan*/  TRUE ; 

BOOL scic_sds_controller_has_remote_devices_stopping(
   SCIC_SDS_CONTROLLER_T * this_controller
)
{
   U32 index;

   for (index = 0; index < this_controller->remote_node_entries; index++)
   {
      if (
            (this_controller->device_table[index] != NULL)
         && (
               this_controller->device_table[index]->parent.state_machine.current_state_id
            == SCI_BASE_REMOTE_DEVICE_STATE_STOPPING
            )
         )
      {
         return TRUE;
      }
   }

   return FALSE;
}