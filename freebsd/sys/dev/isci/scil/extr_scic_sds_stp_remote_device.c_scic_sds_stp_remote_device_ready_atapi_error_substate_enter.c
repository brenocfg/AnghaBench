#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_ATAPI_ERROR ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_stp_remote_device_ready_substate_handler_table ; 

__attribute__((used)) static
void scic_sds_stp_remote_device_ready_atapi_error_substate_enter(
   SCI_BASE_OBJECT_T * device
)
{
   SCIC_SDS_REMOTE_DEVICE_T * this_device;

   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;

   SET_STATE_HANDLER(
      this_device,
      scic_sds_stp_remote_device_ready_substate_handler_table,
      SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_ATAPI_ERROR
   );
}