#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ current_state_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_16__ {TYPE_2__ parent; } ;
struct TYPE_15__ {int /*<<< orphan*/  request_count; TYPE_9__ ready_substate_machine; int /*<<< orphan*/  core_object; } ;
struct TYPE_13__ {scalar_t__ attached_smp_target; } ;
struct TYPE_12__ {TYPE_4__ bits; } ;
struct TYPE_14__ {TYPE_3__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* start_handler ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_5__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_6__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_7__ SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 scalar_t__ SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_TASK_MGMT ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_remote_device_ready_operational_start_high_priority_io_handler(
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * io_request
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;
   SCIF_SAS_IO_REQUEST_T    * fw_io     = (SCIF_SAS_IO_REQUEST_T*) io_request;

   SMP_DISCOVER_RESPONSE_PROTOCOLS_T  dev_protocols;

   scic_remote_device_get_protocols(fw_device->core_object, &dev_protocols);

   if (dev_protocols.u.bits.attached_smp_target)
   {
      //transit to task management state for smp request phase.
      if (fw_device->ready_substate_machine.current_state_id
       != SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_TASK_MGMT)
      {
         sci_base_state_machine_change_state(
            &fw_device->ready_substate_machine,
            SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_TASK_MGMT
         );
      }
   }

   fw_device->request_count++;

   return fw_io->parent.state_handlers->start_handler(&fw_io->parent.parent);
}