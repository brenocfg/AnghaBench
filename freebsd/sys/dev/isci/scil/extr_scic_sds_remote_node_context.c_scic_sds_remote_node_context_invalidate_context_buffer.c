#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  device; int /*<<< orphan*/  remote_node_index; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_valid; } ;
struct TYPE_7__ {TYPE_1__ ssp; } ;
typedef  TYPE_2__ SCU_REMOTE_NODE_CONTEXT_T ;
typedef  TYPE_3__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCU_CONTEXT_COMMAND_POST_RNC_INVALIDATE ; 
 TYPE_2__* scic_sds_controller_get_remote_node_context_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_post_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_remote_node_context_invalidate_context_buffer(
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * this_rnc
)
{
   SCU_REMOTE_NODE_CONTEXT_T *rnc_buffer;

   rnc_buffer = scic_sds_controller_get_remote_node_context_buffer(
      scic_sds_remote_device_get_controller(this_rnc->device),
      this_rnc->remote_node_index
         );

   rnc_buffer->ssp.is_valid = FALSE;

   scic_sds_remote_device_post_request(
      this_rnc->device,
      SCU_CONTEXT_COMMAND_POST_RNC_INVALIDATE
         );
}