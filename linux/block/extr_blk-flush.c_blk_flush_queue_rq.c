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
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_add_to_requeue_list (struct request*,int,int) ; 

__attribute__((used)) static void blk_flush_queue_rq(struct request *rq, bool add_front)
{
	blk_mq_add_to_requeue_list(rq, add_front, true);
}