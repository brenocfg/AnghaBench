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
struct rq_qos {int /*<<< orphan*/  q; } ;
struct blk_iolatency {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct blk_iolatency* BLKIOLATENCY (struct rq_qos*) ; 
 int /*<<< orphan*/  blkcg_deactivate_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkcg_policy_iolatency ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct blk_iolatency*) ; 

__attribute__((used)) static void blkcg_iolatency_exit(struct rq_qos *rqos)
{
	struct blk_iolatency *blkiolat = BLKIOLATENCY(rqos);

	del_timer_sync(&blkiolat->timer);
	blkcg_deactivate_policy(rqos->q, &blkcg_policy_iolatency);
	kfree(blkiolat);
}