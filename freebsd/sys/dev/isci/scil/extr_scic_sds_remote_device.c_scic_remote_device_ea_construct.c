#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  parent; } ;
struct TYPE_15__ {scalar_t__ attached_stp_target; scalar_t__ attached_smp_target; scalar_t__ attached_ssp_target; } ;
struct TYPE_16__ {TYPE_2__ bits; } ;
struct TYPE_17__ {TYPE_3__ u; } ;
struct TYPE_22__ {int device_port_width; int /*<<< orphan*/  owning_port; int /*<<< orphan*/  connection_rate; TYPE_5__ parent; int /*<<< orphan*/  ready_substate_machine; void* has_ready_substate_machine; TYPE_4__ target_protocols; TYPE_1__* rnc; } ;
struct TYPE_19__ {int /*<<< orphan*/  negotiated_physical_link_rate; } ;
struct TYPE_20__ {TYPE_6__ sas1_1; } ;
struct TYPE_21__ {TYPE_7__ u2; } ;
struct TYPE_14__ {int /*<<< orphan*/  remote_node_index; } ;
typedef  TYPE_8__ SMP_RESPONSE_DISCOVER_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_9__ SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_SMP_REMOTE_DEVICE_READY_SUBSTATE_IDLE ; 
 int /*<<< orphan*/  SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_IDLE ; 
 scalar_t__ SCI_SUCCESS ; 
 void* TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_controller_allocate_remote_node_context (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scic_sds_port_get_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_max_allowed_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_info_from_smp_discover_response (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  scic_sds_smp_remote_device_ready_substate_table ; 
 int /*<<< orphan*/  scic_sds_stp_remote_device_ready_substate_table ; 

SCI_STATUS scic_remote_device_ea_construct(
   SCI_REMOTE_DEVICE_HANDLE_T    remote_device,
   SMP_RESPONSE_DISCOVER_T     * discover_response
)
{
   SCI_STATUS status;

   SCIC_SDS_REMOTE_DEVICE_T *this_device;
   SCIC_SDS_CONTROLLER_T    *the_controller;

   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)remote_device;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_device->owning_port),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET,
      "scic_remote_device_ea_sas_construct0x%x, 0x%x) enter\n",
      remote_device, discover_response
   ));

   the_controller = scic_sds_port_get_controller(this_device->owning_port);

   scic_sds_remote_device_get_info_from_smp_discover_response(
      this_device, discover_response
   );

   status = scic_sds_controller_allocate_remote_node_context(
               the_controller,
               this_device,
               &this_device->rnc->remote_node_index
            );

   if (status == SCI_SUCCESS)
   {
      if (this_device->target_protocols.u.bits.attached_ssp_target)
      {
         this_device->has_ready_substate_machine = FALSE;
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

      // For SAS-2 the physical link rate is actually a logical link
      // rate that incorporates multiplexing.  The SCU doesn't
      // incorporate multiplexing and for the purposes of the
      // connection the logical link rate is that same as the
      // physical.  Furthermore, the SAS-2 and SAS-1.1 fields overlay
      // one another, so this code works for both situations.
      this_device->connection_rate = MIN(
         scic_sds_port_get_max_allowed_speed( this_device->owning_port),
         discover_response->u2.sas1_1.negotiated_physical_link_rate
         );

      /// @todo Should I assign the port width by reading all of the phys on the port?
      this_device->device_port_width = 1;
   }

   return status;
}