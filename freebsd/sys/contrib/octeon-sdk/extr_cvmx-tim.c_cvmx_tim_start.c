#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enable_dwb; int enable_timers; } ;
struct TYPE_5__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_tim_control_t ;
struct TYPE_6__ {int /*<<< orphan*/  start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CLOCK_TIM ; 
 int /*<<< orphan*/  CVMX_TIM_REG_FLAGS ; 
 int /*<<< orphan*/  cvmx_clock_get_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_3__ cvmx_tim ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvmx_tim_start(void)
{
    cvmx_tim_control_t control;

    control.u64 = cvmx_read_csr(CVMX_TIM_REG_FLAGS);
    control.s.enable_dwb = 1;
    control.s.enable_timers = 1;

    /* Remember when we started the timers */
    cvmx_tim.start_time = cvmx_clock_get_count(CVMX_CLOCK_TIM);
    cvmx_write_csr(CVMX_TIM_REG_FLAGS, control.u64);
}