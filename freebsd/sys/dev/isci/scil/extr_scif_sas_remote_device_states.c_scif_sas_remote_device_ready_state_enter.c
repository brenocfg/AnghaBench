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
struct TYPE_3__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  ready_substate_machine; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  sci_base_state_machine_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_domain_remote_device_start_complete (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
void scif_sas_remote_device_ready_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)object;

   // Transition immediately into the operational sub-state.
   sci_base_state_machine_start(&fw_device->ready_substate_machine);

#if defined(DISABLE_WIDE_PORTED_TARGETS)
   scif_sas_domain_remote_device_start_complete(fw_device->domain,fw_device);
#endif
}