#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ current_state_id; } ;
struct TYPE_9__ {TYPE_1__ state_machine; } ;
struct TYPE_11__ {TYPE_2__ parent; } ;
struct TYPE_10__ {TYPE_4__* controller; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_3__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_READY ; 
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_STOPPED ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  scif_cb_domain_change_notification (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  scif_sas_domain_state_handler_table ; 

__attribute__((used)) static
void scif_sas_domain_stopped_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIF_SAS_DOMAIN_T * fw_domain = (SCIF_SAS_DOMAIN_T *)object;

   SET_STATE_HANDLER(
      fw_domain,
      scif_sas_domain_state_handler_table,
      SCI_BASE_DOMAIN_STATE_STOPPED
   );

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_domain_stopped_state_enter(0x%x) enter\n",
      fw_domain
   ));

   // A hot unplug of the direct attached device has occurred.  Thus,
   // notify the user. Note, if the controller is not in READY state,
   // mostly likely the controller is in STOPPING or STOPPED state,
   // meaning the controller is in the process of stopping, we should
   // not call back to user in the middle of controller stopping.
   if(fw_domain->controller->parent.state_machine.current_state_id
         == SCI_BASE_CONTROLLER_STATE_READY)
      scif_cb_domain_change_notification(fw_domain->controller, fw_domain);
}