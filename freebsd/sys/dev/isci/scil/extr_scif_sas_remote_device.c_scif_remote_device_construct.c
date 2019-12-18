#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_7__ {int device_port_width; int /*<<< orphan*/  core_object; TYPE_5__ parent; int /*<<< orphan*/  ready_substate_machine; int /*<<< orphan*/  starting_substate_machine; int /*<<< orphan*/ * ea_target_reset_request_scheduled; int /*<<< orphan*/  destination_state; scalar_t__ expander_phy_identifier; int /*<<< orphan*/ * containing_device; int /*<<< orphan*/  is_currently_discovered; scalar_t__ task_request_count; scalar_t__ request_count; int /*<<< orphan*/  operation_status; int /*<<< orphan*/  destruct_when_stopped; TYPE_2__* domain; } ;
typedef  void* SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  scalar_t__ SCI_DOMAIN_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_UNSPECIFIED ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_OPERATIONAL ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_STARTING_SUBSTATE_AWAIT_COMPLETE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_remote_device_construct (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_object_set_association (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_remote_device_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_remote_device_initialize_state_logging (TYPE_1__*) ; 
 int /*<<< orphan*/  scif_sas_remote_device_ready_substate_table ; 
 int /*<<< orphan*/  scif_sas_remote_device_starting_substate_table ; 
 int /*<<< orphan*/  scif_sas_remote_device_state_table ; 

void scif_remote_device_construct(
   SCI_DOMAIN_HANDLE_T          domain,
   void                       * remote_device_memory,
   SCI_REMOTE_DEVICE_HANDLE_T * new_scif_remote_device_handle
)
{
   SCIF_SAS_DOMAIN_T        * fw_domain = (SCIF_SAS_DOMAIN_T *) domain;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                                          remote_device_memory;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_REMOTE_DEVICE,
      "scif_remote_device_construct(0x%x, 0x%x, 0x%x) enter\n",
      domain, remote_device_memory, new_scif_remote_device_handle
   ));

   memset(remote_device_memory, 0, sizeof(SCIF_SAS_REMOTE_DEVICE_T));

   // The user's handle to the remote device evaluates to the memory
   // address where the remote device object is stored.
   *new_scif_remote_device_handle = remote_device_memory;

   fw_device->domain                = fw_domain;
   fw_device->destruct_when_stopped = FALSE;
   //fw_device->parent.is_failed      = FALSE;
   fw_device->operation_status      = SCI_SUCCESS;
   fw_device->request_count         = 0;
   fw_device->task_request_count    = 0;
   fw_device->is_currently_discovered = TRUE;
   fw_device->containing_device       = NULL;
   fw_device->device_port_width       = 1;
   fw_device->expander_phy_identifier = 0;
   fw_device->destination_state       =
      SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_UNSPECIFIED;
   fw_device->ea_target_reset_request_scheduled = NULL;

   // Construct the base object first in order to ensure logging can
   // function.
   sci_base_remote_device_construct(
      &fw_device->parent,
      sci_base_object_get_logger(fw_domain),
      scif_sas_remote_device_state_table
   );

   sci_base_state_machine_construct(
      &fw_device->starting_substate_machine,
      &fw_device->parent.parent,
      scif_sas_remote_device_starting_substate_table,
      SCIF_SAS_REMOTE_DEVICE_STARTING_SUBSTATE_AWAIT_COMPLETE
   );

   sci_base_state_machine_construct(
      &fw_device->ready_substate_machine,
      &fw_device->parent.parent,
      scif_sas_remote_device_ready_substate_table,
      SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_OPERATIONAL
   );

   scif_sas_remote_device_initialize_state_logging(fw_device);

   scic_remote_device_construct(
      fw_domain->core_object,
      ((U8*) remote_device_memory) + sizeof(SCIF_SAS_REMOTE_DEVICE_T),
      &fw_device->core_object
   );

   // Set the association in the core object, so that we are able to
   // determine our framework remote device object from the core remote
   // device.
   sci_object_set_association(fw_device->core_object, fw_device);
}