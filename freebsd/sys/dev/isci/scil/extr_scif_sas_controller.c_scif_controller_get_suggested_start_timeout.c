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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int /*<<< orphan*/  core_object; } ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  scic_controller_get_suggested_start_timeout (int /*<<< orphan*/ ) ; 

U32 scif_controller_get_suggested_start_timeout(
   SCI_CONTROLLER_HANDLE_T  controller
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T*) controller;

   // Validate the user supplied parameters.
   if (controller == SCI_INVALID_HANDLE)
      return 0;

   // Currently we aren't adding any additional time into the suggested
   // timeout value for the start operation.  Simply utilize the core
   // value.
   return scic_controller_get_suggested_start_timeout(fw_controller->core_object);
}