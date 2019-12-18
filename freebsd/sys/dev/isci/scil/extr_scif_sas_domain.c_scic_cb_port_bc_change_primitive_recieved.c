#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ broadcast_change_count; int /*<<< orphan*/  core_object; } ;
typedef  int /*<<< orphan*/  SCI_PORT_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_PHY_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_DOMAIN_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_port_enable_broadcast_change_notification (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_domain_change_notification (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  scif_sas_domain_is_in_smp_activity (TYPE_1__*) ; 

void scic_cb_port_bc_change_primitive_recieved(
   SCI_CONTROLLER_HANDLE_T  controller,
   SCI_PORT_HANDLE_T        port,
   SCI_PHY_HANDLE_T         phy
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T*)
                                   sci_object_get_association(port);

   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T *)
                                           sci_object_get_association(controller);

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scic_cb_port_bc_change_primitive_recieved(0x%x, 0x%x, 0x%x) enter\n",
      controller, port, phy
   ));

   if (fw_domain->broadcast_change_count == 0)
   {  // Enable the BCN detection only if the bcn_count is zero. If bcn_count is
      // not zero at this time, we won't enable BCN detection since all non-zero
      // BCN_count means same to us. Furthermore, we avoid BCN storm by not
      // always enabling the BCN_detection.
      scic_port_enable_broadcast_change_notification(fw_domain->core_object);
   }

   fw_domain->broadcast_change_count++;

   //if there is smp device on this domain that is in the middle of discover
   //process or smp target reset, don't notify the driver layer.
   if( ! scif_sas_domain_is_in_smp_activity(fw_domain) )
      // Notify the user that there is, potentially, a change to the domain.
      scif_cb_domain_change_notification(fw_controller, fw_domain);
}