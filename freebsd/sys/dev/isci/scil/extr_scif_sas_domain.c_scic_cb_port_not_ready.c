#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_5__ {scalar_t__ controller; int /*<<< orphan*/  parent; TYPE_1__* state_handlers; int /*<<< orphan*/  is_port_ready; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* port_not_ready_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SCI_PORT_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCIC_PORT_NOT_READY_RECONFIGURING ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scic_cb_port_not_ready(
   SCI_CONTROLLER_HANDLE_T  controller,
   SCI_PORT_HANDLE_T        port,
   U32                      reason_code
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T*)
                                   sci_object_get_association(port);

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN,
      "scic_cb_port_not_ready(0x%x, 0x%x) enter\n",
      controller, port
   ));

   // The controller supplied with the port should match the controller
   // saved in the domain.
   ASSERT(sci_object_get_association(controller) == fw_domain->controller);

   // There is no need to take action on the port reconfiguring since it is
   // just a change of the port width.
   if (reason_code != SCIC_PORT_NOT_READY_RECONFIGURING)
   {
      fw_domain->is_port_ready = FALSE;

      fw_domain->state_handlers->port_not_ready_handler(
                                    &fw_domain->parent, reason_code);
   }
}