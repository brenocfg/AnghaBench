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
struct ib_mad_queue {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; scalar_t__ count; struct ib_mad_qp_info* qp_info; } ;
struct ib_mad_qp_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_mad_queue(struct ib_mad_qp_info *qp_info,
			   struct ib_mad_queue *mad_queue)
{
	mad_queue->qp_info = qp_info;
	mad_queue->count = 0;
	spin_lock_init(&mad_queue->lock);
	INIT_LIST_HEAD(&mad_queue->list);
}