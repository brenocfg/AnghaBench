#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int phy_index; } ;
struct TYPE_20__ {int active_phy_mask; int /*<<< orphan*/  owning_controller; } ;
struct TYPE_17__ {int /*<<< orphan*/  stp_target; } ;
struct TYPE_18__ {TYPE_1__ bits; } ;
struct TYPE_19__ {TYPE_2__ u; } ;
typedef  TYPE_3__ SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T ;
typedef  TYPE_4__ SCIC_SDS_PORT_T ;
typedef  TYPE_5__ SCIC_SDS_PHY_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_cb_port_link_up (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_clear_invalid_phy (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_phy_get_attached_phy_protocols (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * scic_sds_port_get_controller (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_port_resume_phy (TYPE_4__*,TYPE_5__*) ; 

void scic_sds_port_activate_phy(
   SCIC_SDS_PORT_T * this_port,
   SCIC_SDS_PHY_T  * the_phy,
   BOOL              do_notify_user,
   BOOL              do_resume_phy
)
{
   SCIC_SDS_CONTROLLER_T                      * controller;
   SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T   protocols;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_port),
      SCIC_LOG_OBJECT_PORT,
      "scic_sds_port_activate_phy(0x%x,0x%x,0x%x) enter\n",
      this_port, the_phy, do_notify_user
   ));

   controller = scic_sds_port_get_controller(this_port);
   scic_sds_phy_get_attached_phy_protocols(the_phy, &protocols);

   // If this is sata port then the phy has already been resumed
   if (!protocols.u.bits.stp_target)
   {
      if (do_resume_phy == TRUE)
      {
         scic_sds_port_resume_phy(this_port, the_phy);
      }
   }

   this_port->active_phy_mask |= 1 << the_phy->phy_index;

   scic_sds_controller_clear_invalid_phy(controller, the_phy);

   if (do_notify_user == TRUE)
      scic_cb_port_link_up(this_port->owning_controller, this_port, the_phy);
}