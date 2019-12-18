#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_8__ {TYPE_3__* task_context_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  ncq_tag; } ;
struct TYPE_6__ {TYPE_1__ stp; } ;
struct TYPE_7__ {TYPE_2__ type; } ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_4__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */

void scic_stp_io_request_set_ncq_tag(
   SCI_IO_REQUEST_HANDLE_T  scic_io_request,
   U16                      ncq_tag
)
{
   /**
    * @note This could be made to return an error to the user if the user
    *       attempts to set the NCQ tag in the wrong state.
    */
   SCIC_SDS_REQUEST_T * this_request = (SCIC_SDS_REQUEST_T *)scic_io_request;
   this_request->task_context_buffer->type.stp.ncq_tag = ncq_tag;
}