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
struct rq_qos {int dummy; } ;
struct iolatency_grp {int dummy; } ;
struct blkcg_gq {struct blkcg_gq* parent; } ;
struct blk_iolatency {int /*<<< orphan*/  timer; } ;
struct bio {int bi_opf; struct blkcg_gq* bi_blkg; } ;

/* Variables and functions */
 struct blk_iolatency* BLKIOLATENCY (struct rq_qos*) ; 
 scalar_t__ HZ ; 
 int REQ_SWAP ; 
 int /*<<< orphan*/  __blkcg_iolatency_throttle (struct rq_qos*,struct iolatency_grp*,int,int) ; 
 int bio_issue_as_root_blkg (struct bio*) ; 
 int /*<<< orphan*/  blk_iolatency_enabled (struct blk_iolatency*) ; 
 struct iolatency_grp* blkg_to_lat (struct blkcg_gq*) ; 
 int /*<<< orphan*/  check_scale_change (struct iolatency_grp*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blkcg_iolatency_throttle(struct rq_qos *rqos, struct bio *bio)
{
	struct blk_iolatency *blkiolat = BLKIOLATENCY(rqos);
	struct blkcg_gq *blkg = bio->bi_blkg;
	bool issue_as_root = bio_issue_as_root_blkg(bio);

	if (!blk_iolatency_enabled(blkiolat))
		return;

	while (blkg && blkg->parent) {
		struct iolatency_grp *iolat = blkg_to_lat(blkg);
		if (!iolat) {
			blkg = blkg->parent;
			continue;
		}

		check_scale_change(iolat);
		__blkcg_iolatency_throttle(rqos, iolat, issue_as_root,
				     (bio->bi_opf & REQ_SWAP) == REQ_SWAP);
		blkg = blkg->parent;
	}
	if (!timer_pending(&blkiolat->timer))
		mod_timer(&blkiolat->timer, jiffies + HZ);
}