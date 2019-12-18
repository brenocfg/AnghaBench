#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  owning_port; scalar_t__ is_direct_attached; } ;
struct TYPE_12__ {TYPE_5__* device; int /*<<< orphan*/  remote_node_index; } ;
struct TYPE_9__ {int attached_stp_target; } ;
struct TYPE_10__ {TYPE_1__ bits; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
typedef  TYPE_3__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_4__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_RESUMING_STATE ; 
 int /*<<< orphan*/  SCU_CONTEXT_COMMAND_POST_RNC_RESUME ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  scic_sds_port_setup_transports (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_post_request (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_state_handler_table ; 

__attribute__((used)) static
void scic_sds_remote_node_context_resuming_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * rnc;
   SMP_DISCOVER_RESPONSE_PROTOCOLS_T protocols;
   rnc = (SCIC_SDS_REMOTE_NODE_CONTEXT_T  *)object;

   SET_STATE_HANDLER(
      rnc,
      scic_sds_remote_node_context_state_handler_table,
      SCIC_SDS_REMOTE_NODE_CONTEXT_RESUMING_STATE
         );

   // For direct attached SATA devices we need to clear the TLCR
   // NCQ to TCi tag mapping on the phy and in cases where we
   // resume because of a target reset we also need to update
   // the STPTLDARNI register with the RNi of the device
   scic_remote_device_get_protocols(rnc->device, &protocols);

   if (
      (protocols.u.bits.attached_stp_target == 1)
         && (rnc->device->is_direct_attached)
         )
   {
      scic_sds_port_setup_transports(
         rnc->device->owning_port, rnc->remote_node_index
            );
   }

   scic_sds_remote_device_post_request(
      rnc->device,
      SCU_CONTEXT_COMMAND_POST_RNC_RESUME
         );
}