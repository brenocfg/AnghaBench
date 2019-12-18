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
struct TYPE_2__ {scalar_t__ ct_busy; int /*<<< orphan*/  ct_lock; int /*<<< orphan*/  ct_busy_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* ct ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
callb_unlock_table(void)
{
	mutex_enter(&ct->ct_lock);
	ASSERT(ct->ct_busy != 0);
	ct->ct_busy = 0;
	cv_broadcast(&ct->ct_busy_cv);
	mutex_exit(&ct->ct_lock);
}