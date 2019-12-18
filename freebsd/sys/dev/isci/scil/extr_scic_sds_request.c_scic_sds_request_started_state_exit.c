#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ has_started_substate_machine; int /*<<< orphan*/  started_substate_machine; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_state_machine_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_request_started_state_exit(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_REQUEST_T *this_request = (SCIC_SDS_REQUEST_T *)object;

   if (this_request->has_started_substate_machine == TRUE)
      sci_base_state_machine_stop(&this_request->started_substate_machine);
}