#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* device; } ;
struct TYPE_10__ {TYPE_3__ parent; } ;
struct TYPE_8__ {TYPE_1__* domain; } ;
struct TYPE_7__ {int /*<<< orphan*/ * controller; } ;
typedef  TYPE_4__ SCIF_SAS_TASK_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_sas_controller_free_internal_request (int /*<<< orphan*/ *,TYPE_4__*) ; 

void scif_sas_internal_task_request_destruct(
   SCIF_SAS_TASK_REQUEST_T * fw_internal_task
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller =
      fw_internal_task->parent.device->domain->controller;
   scif_sas_controller_free_internal_request(fw_controller, fw_internal_task);
}