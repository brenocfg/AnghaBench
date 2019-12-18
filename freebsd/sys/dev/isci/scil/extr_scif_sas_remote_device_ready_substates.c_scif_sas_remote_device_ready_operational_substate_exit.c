#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {TYPE_2__* domain; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_cb_remote_device_not_ready (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static
void scif_sas_remote_device_ready_operational_substate_exit(
   SCI_BASE_OBJECT_T *object
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)object;

   // Notify the user that the device has become ready.
   scif_cb_remote_device_not_ready(
      fw_device->domain->controller, fw_device->domain, fw_device
   );
}