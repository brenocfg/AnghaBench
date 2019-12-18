#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * rnc; int /*<<< orphan*/  parent; scalar_t__ started_request_count; int /*<<< orphan*/ * owning_port; } ;
typedef  TYPE_1__* SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  scalar_t__ SCI_PORT_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_remote_device_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_object_set_association (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_initialize_state_logging (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_state_table ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_construct (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scic_remote_device_construct(
   SCI_PORT_HANDLE_T            port,
   void                       * remote_device_memory,
   SCI_REMOTE_DEVICE_HANDLE_T * new_remote_device_handle
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device = (SCIC_SDS_REMOTE_DEVICE_T*)
                                           remote_device_memory;
   SCIC_SDS_PORT_T          *the_port    = (SCIC_SDS_PORT_T*) port;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(the_port),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_construct(0x%x, 0x%x, 0x%x) enter\n",
      port, remote_device_memory, new_remote_device_handle
   ));

   memset(remote_device_memory, 0, sizeof(SCIC_SDS_REMOTE_DEVICE_T));

   *new_remote_device_handle          = this_device;
   this_device->owning_port           = the_port;
   this_device->started_request_count = 0;
   this_device->rnc = (SCIC_SDS_REMOTE_NODE_CONTEXT_T *)
      ((char *)this_device + sizeof(SCIC_SDS_REMOTE_DEVICE_T));

   sci_base_remote_device_construct(
      &this_device->parent,
      sci_base_object_get_logger(the_port),
      scic_sds_remote_device_state_table
   );

   scic_sds_remote_node_context_construct(
      this_device,
      this_device->rnc,
      SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX
   );

   sci_object_set_association(this_device->rnc, this_device);

   scic_sds_remote_device_initialize_state_logging(this_device);
}