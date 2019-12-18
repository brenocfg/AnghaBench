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
struct TYPE_6__ {TYPE_2__* xstate; } ;
struct task_struct {TYPE_3__ thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  fpscr; } ;
struct TYPE_5__ {TYPE_1__ hardfpu; } ;

/* Variables and functions */
 int FPSCR_ROUNDING_MODE (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 

int float_rounding_mode(void)
{
	struct task_struct *tsk = current;
	int roundingMode = FPSCR_ROUNDING_MODE(tsk->thread.xstate->hardfpu.fpscr);
	return roundingMode;
}