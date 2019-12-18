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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_IO_REQUEST_MAXIMUM_TIMER_COUNT ; 

U32 scic_sds_request_get_max_timer_count(void)
{
   return SCIC_SDS_IO_REQUEST_MAXIMUM_TIMER_COUNT;
}