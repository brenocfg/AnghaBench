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
typedef  int U32 ;
struct TYPE_5__ {int /*<<< orphan*/ * sgl_element_pair_buffer; scalar_t__ task_context_buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  sgl_pair_cd; int /*<<< orphan*/  sgl_pair_ab; } ;
typedef  TYPE_1__ SCU_TASK_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCU_SGL_ELEMENT_PAIR_T ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */

SCU_SGL_ELEMENT_PAIR_T *scic_sds_request_get_sgl_element_pair(
   SCIC_SDS_REQUEST_T *this_request,
   U32                 sgl_pair_index
)
{
   SCU_TASK_CONTEXT_T *task_context;

   task_context = (SCU_TASK_CONTEXT_T *)this_request->task_context_buffer;

   if (sgl_pair_index == 0)
   {
      return &task_context->sgl_pair_ab;
   }
   else if (sgl_pair_index == 1)
   {
      return &task_context->sgl_pair_cd;
   }

   return &this_request->sgl_element_pair_buffer[sgl_pair_index - 2];
}