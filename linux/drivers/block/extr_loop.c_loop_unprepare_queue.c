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
struct loop_device {int /*<<< orphan*/  worker_task; int /*<<< orphan*/  worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_flush_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loop_unprepare_queue(struct loop_device *lo)
{
	kthread_flush_worker(&lo->worker);
	kthread_stop(lo->worker_task);
}