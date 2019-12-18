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
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_3__ {int /*<<< orphan*/  function; } ;
typedef  TYPE_1__ SCIF_SAS_TASK_REQUEST_T ;

/* Variables and functions */

U8 scif_sas_task_request_get_function(
   SCIF_SAS_TASK_REQUEST_T *fw_task
)
{
   return fw_task->function;
}