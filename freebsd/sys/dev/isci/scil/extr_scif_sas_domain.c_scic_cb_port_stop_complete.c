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
typedef  int /*<<< orphan*/  SCI_PORT_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 

void scic_cb_port_stop_complete(
   SCI_CONTROLLER_HANDLE_T  controller,
   SCI_PORT_HANDLE_T        port,
   SCI_STATUS               completion_status
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger((SCIF_SAS_DOMAIN_T*)sci_object_get_association(port)),
      SCIF_LOG_OBJECT_DOMAIN,
      "scic_cb_port_stop_complete(0x%x, 0x%x, 0x%x) enter\n",
      controller, port, completion_status
   ));
}