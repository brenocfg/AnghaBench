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
struct TYPE_3__ {int /*<<< orphan*/  task_context_buffer; int /*<<< orphan*/  io_tag; } ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FIELD_OFFSET (int,int /*<<< orphan*/ ) ; 
 int SCU_TASK_CONTEXT_T ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_task_context_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgl_snapshot_ac ; 
 int task_context_buffer ; 

void scic_sds_controller_copy_task_context(
   SCIC_SDS_CONTROLLER_T *this_controller,
   SCIC_SDS_REQUEST_T    *this_request
)
{
   SCU_TASK_CONTEXT_T *task_context_buffer;

   task_context_buffer = scic_sds_controller_get_task_context_buffer(
                            this_controller, this_request->io_tag
                         );

   memcpy(
      task_context_buffer,
      this_request->task_context_buffer,
      SCI_FIELD_OFFSET(SCU_TASK_CONTEXT_T, sgl_snapshot_ac)
   );

   // Now that the soft copy of the TC has been copied into the TC
   // table accessible by the silicon.  Thus, any further changes to
   // the TC (e.g. TC termination) occur in the appropriate location.
   this_request->task_context_buffer = task_context_buffer;
}