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
struct drbd_work_queue {int /*<<< orphan*/  q_wait; int /*<<< orphan*/  q; int /*<<< orphan*/  q_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_init_workqueue(struct drbd_work_queue* wq)
{
	spin_lock_init(&wq->q_lock);
	INIT_LIST_HEAD(&wq->q);
	init_waitqueue_head(&wq->q_wait);
}