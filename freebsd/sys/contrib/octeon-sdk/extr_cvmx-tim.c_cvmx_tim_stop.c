#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ enable_timers; scalar_t__ enable_dwb; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_tim_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_TIM_REG_FLAGS ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvmx_tim_stop(void)
{
    cvmx_tim_control_t control;
    control.u64 = cvmx_read_csr(CVMX_TIM_REG_FLAGS);
    control.s.enable_dwb = 0;
    control.s.enable_timers = 0;
    cvmx_write_csr(CVMX_TIM_REG_FLAGS, control.u64);
}