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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  cvmx_tim_status_t ;
struct TYPE_3__ {scalar_t__* timer_entry_ptr; scalar_t__ const commit_cycles; } ;
typedef  TYPE_1__ cvmx_tim_delete_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CLOCK_TIM ; 
 int /*<<< orphan*/  CVMX_TIM_STATUS_BUSY ; 
 int /*<<< orphan*/  CVMX_TIM_STATUS_SUCCESS ; 
 scalar_t__ cvmx_clock_get_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline cvmx_tim_status_t cvmx_tim_delete_entry(cvmx_tim_delete_t *delete_info)
{
    const uint64_t cycles = cvmx_clock_get_count(CVMX_CLOCK_TIM);

    if ((int64_t)(cycles - delete_info->commit_cycles) < 0)
    {
        /* Timer is far enough away. Safe to delete */
        *delete_info->timer_entry_ptr = 0;
        return CVMX_TIM_STATUS_SUCCESS;
    }
    else
    {
        /* Timer is passed the commit time. It cannot be stopped */
        return CVMX_TIM_STATUS_BUSY;
    }
}