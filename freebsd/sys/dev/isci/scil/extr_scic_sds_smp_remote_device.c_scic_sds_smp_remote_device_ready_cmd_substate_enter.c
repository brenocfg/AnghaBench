#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * working_request; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_REMOTE_DEVICE_NOT_READY_SMP_REQUEST_STARTED ; 
 int /*<<< orphan*/  SCIC_SDS_SMP_REMOTE_DEVICE_READY_SUBSTATE_CMD ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_remote_device_not_ready (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_smp_remote_device_ready_substate_handler_table ; 

__attribute__((used)) static
void scic_sds_smp_remote_device_ready_cmd_substate_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device = (SCIC_SDS_REMOTE_DEVICE_T *)object;

   ASSERT(this_device->working_request != NULL);

   SET_STATE_HANDLER(
      this_device,
      scic_sds_smp_remote_device_ready_substate_handler_table,
      SCIC_SDS_SMP_REMOTE_DEVICE_READY_SUBSTATE_CMD
   );

   scic_cb_remote_device_not_ready(
      scic_sds_remote_device_get_controller(this_device),
      this_device,
      SCIC_REMOTE_DEVICE_NOT_READY_SMP_REQUEST_STARTED
   );
}