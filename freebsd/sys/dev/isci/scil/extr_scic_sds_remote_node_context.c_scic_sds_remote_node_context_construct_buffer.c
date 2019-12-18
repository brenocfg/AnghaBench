#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {TYPE_12__* device; int /*<<< orphan*/  remote_node_index; } ;
struct TYPE_27__ {scalar_t__ oaf_more_compatibility_features; scalar_t__ oaf_source_zone_group; scalar_t__ oaf_features; int /*<<< orphan*/  oaf_connection_rate; scalar_t__ initial_arbitration_wait_time; int /*<<< orphan*/  connection_inactivity_timeout; int /*<<< orphan*/  connection_occupancy_timeout; scalar_t__ arbitration_wait_time; scalar_t__ function_number; void* is_remote_node_context; void* is_valid; void* check_bit; void* nexus_loss_timer_enable; void* remote_sas_address_lo; void* remote_sas_address_hi; int /*<<< orphan*/  logical_port_index; int /*<<< orphan*/  remote_node_port_width; int /*<<< orphan*/  remote_node_index; } ;
struct TYPE_28__ {TYPE_7__ ssp; } ;
struct TYPE_25__ {int /*<<< orphan*/  ssp_inactivity_timeout; int /*<<< orphan*/  ssp_max_occupancy_timeout; int /*<<< orphan*/  stp_inactivity_timeout; int /*<<< orphan*/  stp_max_occupancy_timeout; } ;
struct TYPE_26__ {TYPE_5__ sds1; } ;
struct TYPE_22__ {scalar_t__ attached_stp_target; scalar_t__ attached_sata_device; } ;
struct TYPE_23__ {TYPE_2__ bits; } ;
struct TYPE_24__ {TYPE_3__ u; } ;
struct TYPE_21__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_20__ {int /*<<< orphan*/  connection_rate; TYPE_4__ target_protocols; TYPE_1__ device_address; int /*<<< orphan*/  device_port_width; } ;
struct TYPE_19__ {TYPE_6__ user_parameters; } ;
typedef  TYPE_8__ SCU_REMOTE_NODE_CONTEXT_T ;
typedef  TYPE_9__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;
typedef  TYPE_10__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 void* FALSE ; 
 void* SCIC_SWAP_DWORD (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int,int) ; 
 TYPE_8__* scic_sds_controller_get_remote_node_context_buffer (TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* scic_sds_remote_device_get_controller (TYPE_12__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_port_index (TYPE_12__*) ; 
 int scic_sds_remote_device_node_count (TYPE_12__*) ; 

void scic_sds_remote_node_context_construct_buffer(
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * this_rnc
      )
{
   SCU_REMOTE_NODE_CONTEXT_T * rnc;
   SCIC_SDS_CONTROLLER_T     * the_controller;

   the_controller = scic_sds_remote_device_get_controller(this_rnc->device);

   rnc = scic_sds_controller_get_remote_node_context_buffer(
      the_controller, this_rnc->remote_node_index);

   memset(
      rnc,
      0x00,
      sizeof(SCU_REMOTE_NODE_CONTEXT_T)
         * scic_sds_remote_device_node_count(this_rnc->device)
         );

   rnc->ssp.remote_node_index = this_rnc->remote_node_index;
   rnc->ssp.remote_node_port_width = this_rnc->device->device_port_width;
   rnc->ssp.logical_port_index =
      scic_sds_remote_device_get_port_index(this_rnc->device);

   rnc->ssp.remote_sas_address_hi = SCIC_SWAP_DWORD(this_rnc->device->device_address.high);
   rnc->ssp.remote_sas_address_lo = SCIC_SWAP_DWORD(this_rnc->device->device_address.low);

   rnc->ssp.nexus_loss_timer_enable = TRUE;
   rnc->ssp.check_bit               = FALSE;
   rnc->ssp.is_valid                = FALSE;
   rnc->ssp.is_remote_node_context  = TRUE;
   rnc->ssp.function_number         = 0;

   rnc->ssp.arbitration_wait_time = 0;


   if (
      this_rnc->device->target_protocols.u.bits.attached_sata_device
         || this_rnc->device->target_protocols.u.bits.attached_stp_target
         )
   {
      rnc->ssp.connection_occupancy_timeout =
         the_controller->user_parameters.sds1.stp_max_occupancy_timeout;
      rnc->ssp.connection_inactivity_timeout =
         the_controller->user_parameters.sds1.stp_inactivity_timeout;
   }
   else
   {
      rnc->ssp.connection_occupancy_timeout  =
         the_controller->user_parameters.sds1.ssp_max_occupancy_timeout;
      rnc->ssp.connection_inactivity_timeout =
         the_controller->user_parameters.sds1.ssp_inactivity_timeout;
   }

   rnc->ssp.initial_arbitration_wait_time = 0;

   // Open Address Frame Parameters
   rnc->ssp.oaf_connection_rate = this_rnc->device->connection_rate;
   rnc->ssp.oaf_features = 0;
   rnc->ssp.oaf_source_zone_group = 0;
   rnc->ssp.oaf_more_compatibility_features = 0;
}