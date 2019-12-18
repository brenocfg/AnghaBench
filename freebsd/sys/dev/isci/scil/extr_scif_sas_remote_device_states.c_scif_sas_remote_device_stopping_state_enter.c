#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ operation_status; TYPE_1__* state_handlers; int /*<<< orphan*/  core_object; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* stop_complete_handler ) (TYPE_2__*,scalar_t__) ;} ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STOPPING ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_remote_device_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_remote_device_state_handler_table ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static
void scif_sas_remote_device_stopping_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)object;

   SET_STATE_HANDLER(
      fw_device,
      scif_sas_remote_device_state_handler_table,
      SCI_BASE_REMOTE_DEVICE_STATE_STOPPING
   );

   fw_device->operation_status = scic_remote_device_stop(
                                    fw_device->core_object,
                                    SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT
                                 );

   // If there was a failure, then transition directly to the stopped state.
   if (fw_device->operation_status != SCI_SUCCESS)
   {
      /**
       * @todo We may want to consider adding handling to reset the
       *       structure data for the framework and core devices here
       *       in order to help aid recovery.
       */

      fw_device->state_handlers->stop_complete_handler(
         fw_device, fw_device->operation_status
      );
   }
}