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
struct rq_wb {int /*<<< orphan*/  cb; int /*<<< orphan*/  last_issue; } ;
struct rq_qos {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;
typedef  enum wbt_flags { ____Placeholder_wbt_flags } wbt_flags ;

/* Variables and functions */
 struct rq_wb* RQWB (struct rq_qos*) ; 
 int WBT_READ ; 
 int WBT_TRACKED ; 
 int /*<<< orphan*/  __wbt_wait (struct rq_wb*,int,int /*<<< orphan*/ ) ; 
 int bio_to_wbt_flags (struct rq_wb*,struct bio*) ; 
 int /*<<< orphan*/  blk_stat_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwb_arm_timer (struct rq_wb*) ; 
 int /*<<< orphan*/  wb_timestamp (struct rq_wb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wbt_wait(struct rq_qos *rqos, struct bio *bio)
{
	struct rq_wb *rwb = RQWB(rqos);
	enum wbt_flags flags;

	flags = bio_to_wbt_flags(rwb, bio);
	if (!(flags & WBT_TRACKED)) {
		if (flags & WBT_READ)
			wb_timestamp(rwb, &rwb->last_issue);
		return;
	}

	__wbt_wait(rwb, flags, bio->bi_opf);

	if (!blk_stat_is_active(rwb->cb))
		rwb_arm_timer(rwb);
}