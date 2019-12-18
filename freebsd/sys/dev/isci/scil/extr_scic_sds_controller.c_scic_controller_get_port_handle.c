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
typedef  size_t U8 ;
struct TYPE_2__ {size_t logical_port_entries; int /*<<< orphan*/ * port_table; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/ * SCI_PORT_HANDLE_T ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PORT ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 

SCI_STATUS scic_controller_get_port_handle(
   SCI_CONTROLLER_HANDLE_T controller,
   U8                      port_index,
   SCI_PORT_HANDLE_T *     port_handle
)
{
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_controller_get_port_handle(0x%x, 0x%x, 0x%x) enter\n",
      controller, port_index, port_handle
   ));

   if (port_index < this_controller->logical_port_entries)
   {
      *port_handle = &this_controller->port_table[port_index];

      return SCI_SUCCESS;
   }

   return SCI_FAILURE_INVALID_PORT;
}