#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ U32 ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_CONTROLLER_MAX_TIMER_COUNT ; 
 scalar_t__ scic_sds_phy_get_max_timer_count () ; 
 scalar_t__ scic_sds_port_get_max_timer_count () ; 

U32 scic_sds_controller_get_max_timer_count(void)
{
   return   SCIC_SDS_CONTROLLER_MAX_TIMER_COUNT
          + scic_sds_port_get_max_timer_count()
          + scic_sds_phy_get_max_timer_count();
}