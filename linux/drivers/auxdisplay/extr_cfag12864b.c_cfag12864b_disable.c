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

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfag12864b_mutex ; 
 scalar_t__ cfag12864b_updating ; 
 int /*<<< orphan*/  cfag12864b_work ; 
 int /*<<< orphan*/  cfag12864b_workqueue ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cfag12864b_disable(void)
{
	mutex_lock(&cfag12864b_mutex);

	if (cfag12864b_updating) {
		cfag12864b_updating = 0;
		cancel_delayed_work(&cfag12864b_work);
		flush_workqueue(cfag12864b_workqueue);
	}

	mutex_unlock(&cfag12864b_mutex);
}