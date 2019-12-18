#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_26__ {int /*<<< orphan*/  phy_mask; } ;
struct TYPE_23__ {int /*<<< orphan*/  parent; } ;
struct TYPE_20__ {scalar_t__ attached_smp_target; scalar_t__ attached_stp_target; scalar_t__ attached_ssp_target; } ;
struct TYPE_21__ {TYPE_2__ bits; int /*<<< orphan*/  all; } ;
struct TYPE_22__ {TYPE_3__ u; } ;
struct TYPE_25__ {int device_port_width; TYPE_10__* owning_port; int /*<<< orphan*/  connection_rate; TYPE_5__ parent; int /*<<< orphan*/  ready_substate_machine; void* has_ready_substate_machine; TYPE_4__ target_protocols; int /*<<< orphan*/  device_address; int /*<<< orphan*/  rnc; int /*<<< orphan*/  is_atapi; void* is_direct_attached; } ;
struct TYPE_19__ {int /*<<< orphan*/  all; } ;
struct TYPE_24__ {TYPE_1__ u; } ;
struct TYPE_18__ {int /*<<< orphan*/  owning_controller; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_6__ SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_7__ SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_8__ SCIC_PORT_PROPERTIES_T ;

/* Variables and functions */
 void* FALSE ; 
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_SMP_REMOTE_DEVICE_READY_SUBSTATE_IDLE ; 
 int /*<<< orphan*/  SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_IDLE ; 
 int /*<<< orphan*/  SCI_GET_BITS_SET_COUNT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SCI_SUCCESS ; 
 void* TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_10__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_port_get_properties (TYPE_10__*,TYPE_8__*) ; 
 scalar_t__ scic_sds_controller_allocate_remote_node_context (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_get_attached_protocols (TYPE_10__*,TYPE_6__*) ; 
 int /*<<< orphan*/  scic_sds_port_get_attached_sas_address (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_get_max_allowed_speed (TYPE_10__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_is_atapi (TYPE_7__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_set_remote_node_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_smp_remote_device_ready_substate_table ; 
 int /*<<< orphan*/  scic_sds_stp_remote_device_ready_substate_table ; 

SCI_STATUS scic_remote_device_da_construct(
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device
)
{
   SCI_STATUS                status;
   U16                       remote_node_index;
   SCIC_SDS_REMOTE_DEVICE_T *this_device = (SCIC_SDS_REMOTE_DEVICE_T*)
                                           remote_device;
   SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T  protocols;
   SCIC_PORT_PROPERTIES_T  properties;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_device->owning_port),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_da_construct(0x%x) enter\n",
      remote_device
   ));

   // This information is request to determine how many remote node context
   // entries will be needed to store the remote node.
   scic_sds_port_get_attached_protocols(this_device->owning_port,&protocols);
   this_device->target_protocols.u.all = protocols.u.all;
   this_device->is_direct_attached = TRUE;
#if !defined(DISABLE_ATAPI)
   this_device->is_atapi = scic_sds_remote_device_is_atapi(this_device);
#endif

   scic_port_get_properties(this_device->owning_port, &properties);
   //Get accurate port width from port's phy mask for a DA device.
   SCI_GET_BITS_SET_COUNT(properties.phy_mask, this_device->device_port_width);

   status = scic_sds_controller_allocate_remote_node_context(
               this_device->owning_port->owning_controller,
               this_device,
               &remote_node_index
            );

   if (status == SCI_SUCCESS)
   {
      scic_sds_remote_node_context_set_remote_node_index(
         this_device->rnc, remote_node_index
      );

      scic_sds_port_get_attached_sas_address(
         this_device->owning_port, &this_device->device_address
      );

      if (this_device->target_protocols.u.bits.attached_ssp_target)
      {
         this_device->has_ready_substate_machine = FALSE;
      }
      else if (this_device->target_protocols.u.bits.attached_stp_target)
      {
         this_device->has_ready_substate_machine = TRUE;

         sci_base_state_machine_construct(
            &this_device->ready_substate_machine,
            &this_device->parent.parent,
            scic_sds_stp_remote_device_ready_substate_table,
            SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_IDLE
         );
      }
      else if (this_device->target_protocols.u.bits.attached_smp_target)
      {
         this_device->has_ready_substate_machine = TRUE;

         //add the SMP ready substate machine construction here
         sci_base_state_machine_construct(
            &this_device->ready_substate_machine,
            &this_device->parent.parent,
            scic_sds_smp_remote_device_ready_substate_table,
            SCIC_SDS_SMP_REMOTE_DEVICE_READY_SUBSTATE_IDLE
         );
      }

      this_device->connection_rate = scic_sds_port_get_max_allowed_speed(
                                        this_device->owning_port
                                     );

      /// @todo Should I assign the port width by reading all of the phys on the port?
      this_device->device_port_width = 1;
   }

   return status;
}