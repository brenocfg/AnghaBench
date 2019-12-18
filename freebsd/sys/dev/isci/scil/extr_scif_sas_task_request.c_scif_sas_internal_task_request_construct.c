#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_3__ {int /*<<< orphan*/  is_internal; } ;
struct TYPE_4__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_TASK_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_2__ SCIF_SAS_TASK_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scif_sas_task_request_generic_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_STATUS scif_sas_internal_task_request_construct(
   SCI_CONTROLLER_HANDLE_T      scif_controller,
   SCI_REMOTE_DEVICE_HANDLE_T   scif_remote_device,
   U16                          io_tag,
   void                       * task_request_memory,
   SCI_TASK_REQUEST_HANDLE_T  * scif_task_request,
   U8                           task_function
)
{
   SCI_STATUS                 status;
   SCIF_SAS_TASK_REQUEST_T *  fw_task;

   status = scif_sas_task_request_generic_construct(
               scif_controller,
               scif_remote_device,
               io_tag,
               NULL,
               task_request_memory,
               scif_task_request,
               task_function
            );

   fw_task = (SCIF_SAS_TASK_REQUEST_T *)task_request_memory;

   fw_task->parent.is_internal = TRUE;

   return status;
}