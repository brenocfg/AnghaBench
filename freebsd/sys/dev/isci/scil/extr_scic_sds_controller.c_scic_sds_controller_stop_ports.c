#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_10__ {size_t logical_port_entries; TYPE_2__* port_table; } ;
struct TYPE_9__ {scalar_t__ (* stop_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  logical_port_index; int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_7__ {TYPE_3__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_4__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_FAILURE_INVALID_STATE ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_controller_stop_ports(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U32        index;
   SCI_STATUS status;
   SCI_STATUS port_status;

   status = SCI_SUCCESS;

   for (index = 0; index < this_controller->logical_port_entries; index++)
   {
      port_status = this_controller->port_table[index].
         state_handlers->parent.stop_handler(&this_controller->port_table[index].parent);
      if (
            (port_status != SCI_SUCCESS)
         && (port_status != SCI_FAILURE_INVALID_STATE)
         )
      {
         status = SCI_FAILURE;

         SCIC_LOG_WARNING((
            sci_base_object_get_logger(this_controller),
            SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_PORT,
            "Controller stop operation failed to stop port %d because of status %d.\n",
            this_controller->port_table[index].logical_port_index, port_status
         ));
      }
   }

   return status;
}