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
typedef  int /*<<< orphan*/  U16 ;

/* Variables and functions */
 scalar_t__ scic_sds_controller_get_min_timer_count () ; 
 scalar_t__ scic_sds_remote_device_get_min_timer_count () ; 
 scalar_t__ scic_sds_request_get_min_timer_count () ; 

U16 scic_library_get_min_timer_count(void)
{
   return (U16) (scic_sds_controller_get_min_timer_count()
               + scic_sds_remote_device_get_min_timer_count()
               + scic_sds_request_get_min_timer_count());
}