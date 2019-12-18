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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int bpt_nsaved; } ;

/* Variables and functions */
 TYPE_1__* task_thread_info (struct task_struct*) ; 

void user_enable_single_step(struct task_struct *child)
{
	/* Mark single stepping.  */
	task_thread_info(child)->bpt_nsaved = -1;
}