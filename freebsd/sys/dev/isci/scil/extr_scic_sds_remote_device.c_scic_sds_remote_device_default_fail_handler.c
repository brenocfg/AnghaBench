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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_base_state_machine (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_remote_device_default_fail_handler(
   SCI_BASE_REMOTE_DEVICE_T *device
)
{
   SCIC_LOG_WARNING((
      sci_base_object_get_logger((SCIC_SDS_REMOTE_DEVICE_T *)device),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_SMP_REMOTE_TARGET |
      SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
      "SCIC Remote Device requested to fail while in wrong state %d\n",
      sci_base_state_machine_get_state(
         scic_sds_remote_device_get_base_state_machine((SCIC_SDS_REMOTE_DEVICE_T *)device))
   ));

   return SCI_FAILURE_INVALID_STATE;
}