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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_base_state_machine (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_port_default_destruct_handler(
   SCI_BASE_PORT_T *port
)
{
   SCIC_LOG_WARNING((
      sci_base_object_get_logger((SCIC_SDS_PORT_T *)port),
      SCIC_LOG_OBJECT_PORT,
      "SCIC Port 0x%08x requested to destruct while in invalid state %d\n",
      port,
      sci_base_state_machine_get_state(
         scic_sds_port_get_base_state_machine((SCIC_SDS_PORT_T *)port))
   ));

   return SCI_FAILURE_INVALID_STATE;
}