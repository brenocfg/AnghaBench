#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  timer_started; int /*<<< orphan*/  timer; } ;
struct TYPE_6__ {TYPE_1__ power_control; } ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scic_cb_timer_start (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_controller_power_control_timer_start(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   scic_cb_timer_start(
      this_controller, this_controller->power_control.timer,
      SCIC_SDS_CONTROLLER_POWER_CONTROL_INTERVAL
   );

   this_controller->power_control.timer_started = TRUE;
}