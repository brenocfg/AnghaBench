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
struct ib_cq {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_comp_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ib_cq_completion_workqueue(struct ib_cq *cq, void *private)
{
	queue_work(ib_comp_wq, &cq->work);
}