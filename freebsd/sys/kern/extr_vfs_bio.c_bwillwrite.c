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
 scalar_t__ PRIBIO ; 
 int /*<<< orphan*/  bdirtylock ; 
 int bdirtywait ; 
 scalar_t__ buf_dirty_count_severe () ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
bwillwrite(void)
{

	if (buf_dirty_count_severe()) {
		mtx_lock(&bdirtylock);
		while (buf_dirty_count_severe()) {
			bdirtywait = 1;
			msleep(&bdirtywait, &bdirtylock, (PRIBIO + 4),
			    "flswai", 0);
		}
		mtx_unlock(&bdirtylock);
	}
}