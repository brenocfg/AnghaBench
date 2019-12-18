#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int align_ctl; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */

int set_unalign_ctl(struct task_struct *tsk, unsigned int val)
{
	tsk->thread.align_ctl = val;
	return 0;
}