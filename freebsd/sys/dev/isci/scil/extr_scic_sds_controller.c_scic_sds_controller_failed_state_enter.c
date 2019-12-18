#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ error; } ;
struct TYPE_8__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
 scalar_t__ SCI_CONTROLLER_FATAL_MEMORY_ERROR ; 
 int /*<<< orphan*/  scic_cb_controller_error (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_controller_release_resource (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_controller_set_base_state_handlers (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_terminate_all_requests (TYPE_2__*) ; 

__attribute__((used)) static
void scic_sds_controller_failed_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller= (SCIC_SDS_CONTROLLER_T *)object;

   scic_sds_controller_set_base_state_handlers(
      this_controller, SCI_BASE_CONTROLLER_STATE_FAILED);

   if (this_controller->parent.error == SCI_CONTROLLER_FATAL_MEMORY_ERROR)
   scic_sds_terminate_all_requests(this_controller);
   else
       scic_sds_controller_release_resource(this_controller);

   //notify framework the controller failed.
   scic_cb_controller_error(this_controller,
           this_controller->parent.error);
}