#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* state_handlers; } ;
struct TYPE_11__ {int /*<<< orphan*/  phy_index; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* link_up_handler ) (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  TYPE_2__ SCIC_SDS_PHY_T ;
typedef  TYPE_3__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 

void scic_sds_controller_link_up(
   SCIC_SDS_CONTROLLER_T *this_controller,
   SCIC_SDS_PORT_T       *the_port,
   SCIC_SDS_PHY_T        *the_phy
)
{
   if (this_controller->state_handlers->link_up_handler != NULL)
   {
      this_controller->state_handlers->link_up_handler(
         this_controller, the_port, the_phy);
   }
   else
   {
      SCIC_LOG_INFO((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller linkup event from phy %d in unexpected state %d\n",
         the_phy->phy_index,
         sci_base_state_machine_get_state(
            scic_sds_controller_get_base_state_machine(this_controller))
      ));
   }
}