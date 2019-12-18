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
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  SCI_TASK_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  scif_cb_task_request_get_function (void*) ; 
 int /*<<< orphan*/  scif_sas_task_request_generic_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_STATUS scif_task_request_construct(
   SCI_CONTROLLER_HANDLE_T      scif_controller,
   SCI_REMOTE_DEVICE_HANDLE_T   scif_remote_device,
   U16                          io_tag,
   void                       * user_task_request_object,
   void                       * task_request_memory,
   SCI_TASK_REQUEST_HANDLE_T  * scif_task_request
)
{
   SCI_STATUS  status;
   U8          task_function =
                scif_cb_task_request_get_function(user_task_request_object);

   status = scif_sas_task_request_generic_construct(
               scif_controller,
               scif_remote_device,
               io_tag,
               user_task_request_object,
               task_request_memory,
               scif_task_request,
               task_function
            );

   return status;
}