#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_9__ {int /*<<< orphan*/ * timer; } ;
struct TYPE_10__ {int /*<<< orphan*/ * phy_table; int /*<<< orphan*/ * port_table; int /*<<< orphan*/  port_agent; int /*<<< orphan*/ * timeout_timer; TYPE_1__ power_control; int /*<<< orphan*/ * phy_startup_timer; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_INITIALIZATION ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 size_t SCI_MAX_PHYS ; 
 size_t SCI_MAX_PORTS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_cb_timer_destroy (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_release_resource (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_configuration_agent_release_resource (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_release_resource (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_release_resource(
   SCIC_SDS_CONTROLLER_T * this_controller
)
{
   SCIC_SDS_PORT_T * port;
   SCIC_SDS_PHY_T * phy;
   U8 index;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_INITIALIZATION,
      "scic_sds_controller_release_resource(0x%x) enter\n",
      this_controller
   ));

   if(this_controller->phy_startup_timer != NULL)
   {
      scic_cb_timer_destroy(this_controller, this_controller->phy_startup_timer);
      this_controller->phy_startup_timer = NULL;
   }

   if(this_controller->power_control.timer != NULL)
   {
      scic_cb_timer_destroy(this_controller, this_controller->power_control.timer);
      this_controller->power_control.timer = NULL;
   }

   if(this_controller->timeout_timer != NULL)
   {
      scic_cb_timer_destroy(this_controller, this_controller->timeout_timer);
      this_controller->timeout_timer = NULL;
   }

   scic_sds_port_configuration_agent_release_resource(
      this_controller,
      &this_controller->port_agent);

   for(index = 0; index < SCI_MAX_PORTS+1; index++)
   {
      port = &this_controller->port_table[index];
      scic_sds_port_release_resource(this_controller, port);
   }

   for(index = 0; index < SCI_MAX_PHYS; index++)
   {
      phy = &this_controller->phy_table[index];
      scic_sds_phy_release_resource(this_controller, phy);
   }

   return SCI_SUCCESS;
}