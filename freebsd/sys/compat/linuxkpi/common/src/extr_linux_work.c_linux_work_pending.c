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
struct work_struct {int /*<<< orphan*/  state; } ;

/* Variables and functions */
#define  WORK_ST_CANCEL 130 
#define  WORK_ST_TASK 129 
#define  WORK_ST_TIMER 128 
 int atomic_read (int /*<<< orphan*/ *) ; 

bool
linux_work_pending(struct work_struct *work)
{
	switch (atomic_read(&work->state)) {
	case WORK_ST_TIMER:
	case WORK_ST_TASK:
	case WORK_ST_CANCEL:
		return (true);
	default:
		return (false);
	}
}