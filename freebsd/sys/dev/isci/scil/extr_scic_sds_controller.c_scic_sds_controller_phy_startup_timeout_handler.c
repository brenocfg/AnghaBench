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
struct TYPE_3__ {int /*<<< orphan*/  phy_startup_timer_pending; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ scic_sds_controller_start_next_phy (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_controller_phy_startup_timeout_handler(
   void *controller
)
{
   SCI_STATUS status;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   this_controller->phy_startup_timer_pending = FALSE;

   status = SCI_FAILURE;

   while (status != SCI_SUCCESS)
   {
      status = scic_sds_controller_start_next_phy(this_controller);
   }
}