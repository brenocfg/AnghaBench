#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
typedef  scalar_t__ U16 ;
struct TYPE_13__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_15__ {scalar_t__ internal_request_entries; TYPE_4__ parent; int /*<<< orphan*/  core_object; TYPE_3__* domains; int /*<<< orphan*/  internal_request_memory_pool; TYPE_5__* mdes; } ;
struct TYPE_14__ {void* virtual_address; } ;
struct TYPE_11__ {scalar_t__ status; } ;
struct TYPE_10__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_12__ {TYPE_2__ operation; TYPE_1__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_5__ SCI_PHYSICAL_MEMORY_DESCRIPTOR_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_6__ SCIF_SAS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  POINTER_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_CONTROLLER ; 
 int SCIF_LOG_OBJECT_INITIALIZATION ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 size_t SCIF_SAS_MDE_INTERNAL_IO ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_STARTING ; 
 int /*<<< orphan*/  SCI_BASE_DOMAIN_STATE_STARTING ; 
 scalar_t__ SCI_MAX_DOMAINS ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_6__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_controller_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_start_internal_io_task_create (TYPE_6__*) ; 
 scalar_t__ scif_sas_controller_validate_mdl (TYPE_6__*) ; 
 scalar_t__ scif_sas_internal_request_get_object_size () ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_initialized_start_handler(
   SCI_BASE_CONTROLLER_T * controller,
   U32                     timeout
)
{
   SCI_STATUS              status        = SCI_SUCCESS;
   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T *)controller;
   U16                     index         = 0;

   SCI_PHYSICAL_MEMORY_DESCRIPTOR_T internal_reqeust_mde =
      fw_controller->mdes[SCIF_SAS_MDE_INTERNAL_IO];

   void * internal_request_virtual_address =  internal_reqeust_mde.virtual_address;
   POINTER_UINT address = (POINTER_UINT)internal_request_virtual_address;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_INITIALIZATION,
      "scif_sas_controller_initialized_start_handler(0x%x, 0x%x) enter\n",
      controller, timeout
   ));

   sci_base_state_machine_change_state(
      &fw_controller->parent.state_machine,
      SCI_BASE_CONTROLLER_STATE_STARTING
   );

   status = scif_sas_controller_validate_mdl(fw_controller);

   // initialization work for internal request path. It must be done before
   // starting domain.
   if (status == SCI_SUCCESS)
   {
      // fill in the sci_pool for internal requests.
      sci_pool_initialize(fw_controller->internal_request_memory_pool);

      for (index = 0; index < fw_controller->internal_request_entries; index++)
      {
         sci_pool_put(fw_controller->internal_request_memory_pool, address);

         address += scif_sas_internal_request_get_object_size();
      }

      // Using DPC for starting internal IOs, if yes, we need to intialize
      // DPC here.
      scif_cb_start_internal_io_task_create(fw_controller);
   }

   if (status == SCI_SUCCESS)
   {
      // Kick-start the domain state machines and, by association, the
      // core port's.

      // This will ensure we get valid port objects supplied with link up
      // messages.
      for (index = 0;
           (index < SCI_MAX_DOMAINS) && (status == SCI_SUCCESS);
           index++)
      {
         sci_base_state_machine_change_state(
            &fw_controller->domains[index].parent.state_machine,
            SCI_BASE_DOMAIN_STATE_STARTING
         );
         status = fw_controller->domains[index].operation.status;
      }
   }

   // Validate that all the domain state machines began successfully.
   if (status != SCI_SUCCESS)
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_controller),
         SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_INITIALIZATION,
         "Controller:0x%x Domain:0x%x Status:0x%x unable to start\n",
         fw_controller, index, status
      ));

      return status;
   }

   // Attempt to start the core controller.
   status = scic_controller_start(fw_controller->core_object, timeout);
   if (status != SCI_SUCCESS)
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_controller),
         SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_INITIALIZATION,
         "Controller:0x%x Status:0x%x unable to start controller.\n",
         fw_controller, status
      ));

      sci_base_state_machine_change_state(
         &fw_controller->parent.state_machine,
         SCI_BASE_CONTROLLER_STATE_FAILED
      );
   }

   return status;
}