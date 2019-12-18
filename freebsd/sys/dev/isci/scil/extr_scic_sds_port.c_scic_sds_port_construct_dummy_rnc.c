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
typedef  size_t U16 ;
struct TYPE_10__ {int /*<<< orphan*/  physical_port_index; TYPE_1__* owning_controller; } ;
struct TYPE_8__ {size_t remote_node_index; int remote_node_port_width; scalar_t__ arbitration_wait_time; scalar_t__ function_number; void* is_remote_node_context; void* is_valid; void* check_bit; void* nexus_loss_timer_enable; int /*<<< orphan*/  logical_port_index; scalar_t__ remote_sas_address_lo; scalar_t__ remote_sas_address_hi; } ;
struct TYPE_9__ {TYPE_2__ ssp; } ;
struct TYPE_7__ {TYPE_3__* remote_node_context_table; } ;
typedef  TYPE_3__ SCU_REMOTE_NODE_CONTEXT_T ;
typedef  TYPE_4__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void scic_sds_port_construct_dummy_rnc(
   SCIC_SDS_PORT_T *this_port,
   U16              rni
)
{
   SCU_REMOTE_NODE_CONTEXT_T * rnc;

   rnc = &(this_port->owning_controller->remote_node_context_table[rni]);

   memset(rnc, 0, sizeof(SCU_REMOTE_NODE_CONTEXT_T));

   rnc->ssp.remote_sas_address_hi = 0;
   rnc->ssp.remote_sas_address_lo = 0;

   rnc->ssp.remote_node_index = rni;
   rnc->ssp.remote_node_port_width = 1;
   rnc->ssp.logical_port_index = this_port->physical_port_index;

   rnc->ssp.nexus_loss_timer_enable = FALSE;
   rnc->ssp.check_bit = FALSE;
   rnc->ssp.is_valid = TRUE;
   rnc->ssp.is_remote_node_context = TRUE;
   rnc->ssp.function_number = 0;
   rnc->ssp.arbitration_wait_time = 0;
}