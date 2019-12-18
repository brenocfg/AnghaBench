#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; TYPE_2__* state_handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* complete_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_3__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_sds_task_request_complete(
   SCIC_SDS_REQUEST_T *this_request
)
{
   return this_request->state_handlers->parent.complete_handler(&this_request->parent);
}