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
 int /*<<< orphan*/  PVM ; 
 scalar_t__ hirunningspace ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbreqlock ; 
 int runningbufreq ; 
 scalar_t__ runningbufspace ; 

void
waitrunningbufspace(void)
{

	mtx_lock(&rbreqlock);
	while (runningbufspace > hirunningspace) {
		runningbufreq = 1;
		msleep(&runningbufreq, &rbreqlock, PVM, "wdrain", 0);
	}
	mtx_unlock(&rbreqlock);
}