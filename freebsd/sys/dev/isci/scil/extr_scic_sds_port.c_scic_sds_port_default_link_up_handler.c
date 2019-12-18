#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_base_state_machine (int /*<<< orphan*/ *) ; 

void scic_sds_port_default_link_up_handler(
   SCIC_SDS_PORT_T *this_port,
   SCIC_SDS_PHY_T  *phy
)
{
   SCIC_LOG_WARNING((
      sci_base_object_get_logger(this_port),
      SCIC_LOG_OBJECT_PORT,
      "SCIC Port 0x%08x received link_up notification from phy 0x%08x while in invalid state %d\n",
      this_port, phy,
      sci_base_state_machine_get_state(
         scic_sds_port_get_base_state_machine(this_port))
   ));
}