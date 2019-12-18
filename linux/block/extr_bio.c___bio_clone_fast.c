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
struct bio {int /*<<< orphan*/  bi_io_vec; int /*<<< orphan*/  bi_iter; int /*<<< orphan*/  bi_write_hint; int /*<<< orphan*/  bi_ioprio; int /*<<< orphan*/  bi_opf; int /*<<< orphan*/  bi_partno; int /*<<< orphan*/  bi_disk; scalar_t__ bi_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLONED ; 
 int /*<<< orphan*/  BIO_THROTTLED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ BVEC_POOL_IDX (struct bio*) ; 
 int /*<<< orphan*/  bio_clone_blkg_association (struct bio*,struct bio*) ; 
 scalar_t__ bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkcg_bio_issue_init (struct bio*) ; 

void __bio_clone_fast(struct bio *bio, struct bio *bio_src)
{
	BUG_ON(bio->bi_pool && BVEC_POOL_IDX(bio));

	/*
	 * most users will be overriding ->bi_disk with a new target,
	 * so we don't set nor calculate new physical/hw segment counts here
	 */
	bio->bi_disk = bio_src->bi_disk;
	bio->bi_partno = bio_src->bi_partno;
	bio_set_flag(bio, BIO_CLONED);
	if (bio_flagged(bio_src, BIO_THROTTLED))
		bio_set_flag(bio, BIO_THROTTLED);
	bio->bi_opf = bio_src->bi_opf;
	bio->bi_ioprio = bio_src->bi_ioprio;
	bio->bi_write_hint = bio_src->bi_write_hint;
	bio->bi_iter = bio_src->bi_iter;
	bio->bi_io_vec = bio_src->bi_io_vec;

	bio_clone_blkg_association(bio, bio_src);
	blkcg_bio_issue_init(bio);
}