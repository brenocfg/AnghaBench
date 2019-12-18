#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  core_object; TYPE_3__* device; } ;
struct TYPE_10__ {TYPE_4__ parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  core_object; TYPE_2__* domain; } ;
struct TYPE_7__ {TYPE_1__* controller; } ;
struct TYPE_6__ {int /*<<< orphan*/  core_object; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  TYPE_5__ SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_controller_terminate_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_io_request_aborting_abort_handler(
   SCI_BASE_REQUEST_T * io_request
)
{
   SCIF_SAS_IO_REQUEST_T * fw_request = (SCIF_SAS_IO_REQUEST_T *) io_request;

   return scic_controller_terminate_request(
             fw_request->parent.device->domain->controller->core_object,
             fw_request->parent.device->core_object,
             fw_request->parent.core_object
          );
}