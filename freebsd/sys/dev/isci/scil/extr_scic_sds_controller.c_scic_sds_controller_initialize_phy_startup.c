#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  phy_startup_timer_pending; scalar_t__ next_phy_to_start; int /*<<< orphan*/ * phy_startup_timer; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCI_FAILURE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/ * scic_cb_timer_create (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_controller_phy_startup_timeout_handler ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_initialize_phy_startup(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   this_controller->phy_startup_timer = scic_cb_timer_create(
      this_controller,
      scic_sds_controller_phy_startup_timeout_handler,
      this_controller
   );

   if (this_controller->phy_startup_timer == NULL)
   {
      return SCI_FAILURE_INSUFFICIENT_RESOURCES;
   }
   else
   {
      this_controller->next_phy_to_start = 0;
      this_controller->phy_startup_timer_pending = FALSE;
   }

   return SCI_SUCCESS;
}