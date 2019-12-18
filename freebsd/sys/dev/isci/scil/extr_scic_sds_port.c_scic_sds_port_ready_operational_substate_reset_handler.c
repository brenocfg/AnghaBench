#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_5__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_6__ {TYPE_1__ parent; int /*<<< orphan*/  not_ready_reason; int /*<<< orphan*/  timer_handle; int /*<<< orphan*/ ** phy_table; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_PORT_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_PORT_NOT_READY_HARD_RESET_REQUESTED ; 
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_RESETTING ; 
 scalar_t__ SCI_FAILURE_INVALID_PHY ; 
 int /*<<< orphan*/ * SCI_INVALID_HANDLE ; 
 size_t SCI_MAX_PHYS ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ scic_sds_phy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_active_phy (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_get_controller (TYPE_2__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_port_ready_operational_substate_reset_handler(
   SCI_BASE_PORT_T * port,
   U32               timeout
)
{
   SCI_STATUS        status = SCI_FAILURE_INVALID_PHY;
   U32               phy_index;
   SCIC_SDS_PORT_T * this_port = (SCIC_SDS_PORT_T *)port;
   SCIC_SDS_PHY_T  * selected_phy = SCI_INVALID_HANDLE;


   // Select a phy on which we can send the hard reset request.
   for (
         phy_index = 0;
            (phy_index < SCI_MAX_PHYS)
         && (selected_phy == SCI_INVALID_HANDLE);
         phy_index++
       )
   {
      selected_phy = this_port->phy_table[phy_index];

      if (
            (selected_phy != SCI_INVALID_HANDLE)
         && !scic_sds_port_active_phy(this_port, selected_phy)
         )
      {
         // We found a phy but it is not ready select different phy
         selected_phy = SCI_INVALID_HANDLE;
      }
   }

   // If we have a phy then go ahead and start the reset procedure
   if (selected_phy != SCI_INVALID_HANDLE)
   {
      status = scic_sds_phy_reset(selected_phy);

      if (status == SCI_SUCCESS)
      {
         scic_cb_timer_start(
            scic_sds_port_get_controller(this_port),
            this_port->timer_handle,
            timeout
         );

         this_port->not_ready_reason = SCIC_PORT_NOT_READY_HARD_RESET_REQUESTED;

         sci_base_state_machine_change_state(
            &this_port->parent.state_machine,
            SCI_BASE_PORT_STATE_RESETTING
         );
      }
   }

   return status;
}