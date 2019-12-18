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
 int /*<<< orphan*/  dbu_evict_taskq ; 
 int /*<<< orphan*/  taskq_wait (int /*<<< orphan*/ ) ; 

void
dmu_buf_user_evict_wait()
{
	taskq_wait(dbu_evict_taskq);
}