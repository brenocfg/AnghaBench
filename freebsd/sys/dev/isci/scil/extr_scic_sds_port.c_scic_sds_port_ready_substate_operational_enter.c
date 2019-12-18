#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_9__ {int active_phy_mask; int enabled_phy_mask; int /*<<< orphan*/ ** phy_table; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_OPERATIONAL ; 
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  scic_cb_port_ready (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_post_dummy_request (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_resume_phy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_set_ready_state_handlers (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_update_viit_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_write_phy_assignment (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_port_ready_substate_operational_enter(
   SCI_BASE_OBJECT_T *object
)
{
   U32 index;
   SCIC_SDS_PORT_T *this_port = (SCIC_SDS_PORT_T *)object;

   scic_sds_port_set_ready_state_handlers(
      this_port, SCIC_SDS_PORT_READY_SUBSTATE_OPERATIONAL
   );

   scic_cb_port_ready(
      scic_sds_port_get_controller(this_port), this_port
   );

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      if (this_port->phy_table[index] != NULL)
      {
         scic_sds_port_write_phy_assignment(
            this_port, this_port->phy_table[index]
         );

         //if the bit at the index location for active phy mask is set and
         //enabled_phy_mask is not set then resume the phy
         if ( ( (this_port->active_phy_mask ^ this_port->enabled_phy_mask) & (1 << index) ) != 0)
         {
            scic_sds_port_resume_phy (
               this_port,
               this_port->phy_table[index]
            );
         }
      }
   }

   scic_sds_port_update_viit_entry(this_port);

   // Post the dummy task for the port so the hardware can schedule
   // io correctly
   scic_sds_port_post_dummy_request(this_port);
}