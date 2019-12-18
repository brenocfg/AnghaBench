#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rnc; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_RESETTING ; 
 int /*<<< orphan*/  SCI_SOFTWARE_SUSPENSION ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_state_handler_table ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_remote_device_resetting_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device = (SCIC_SDS_REMOTE_DEVICE_T *)object;

   SET_STATE_HANDLER(
      this_device,
      scic_sds_remote_device_state_handler_table,
      SCI_BASE_REMOTE_DEVICE_STATE_RESETTING
   );

   scic_sds_remote_node_context_suspend(
      this_device->rnc, SCI_SOFTWARE_SUSPENSION, NULL, NULL);
}