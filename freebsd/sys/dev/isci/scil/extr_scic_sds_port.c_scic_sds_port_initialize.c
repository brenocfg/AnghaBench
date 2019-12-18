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
struct TYPE_3__ {void* viit_registers; void* port_pe_configuration_register; void* port_task_scheduler_registers; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SUCCESS ; 

SCI_STATUS scic_sds_port_initialize(
   SCIC_SDS_PORT_T *this_port,
   void            *port_task_scheduler_registers,
   void            *port_configuration_regsiter,
   void            *viit_registers
)
{
   this_port->port_task_scheduler_registers  = port_task_scheduler_registers;
   this_port->port_pe_configuration_register = port_configuration_regsiter;
   this_port->viit_registers                 = viit_registers;

   return SCI_SUCCESS;
}