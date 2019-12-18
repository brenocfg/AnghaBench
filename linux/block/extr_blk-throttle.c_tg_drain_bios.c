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
struct throtl_service_queue {int /*<<< orphan*/ * queued; } ;
struct throtl_grp {struct throtl_service_queue service_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  tg_dispatch_one_bio (struct throtl_grp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throtl_dequeue_tg (struct throtl_grp*) ; 
 struct bio* throtl_peek_queued (int /*<<< orphan*/ *) ; 
 struct throtl_grp* throtl_rb_first (struct throtl_service_queue*) ; 

__attribute__((used)) static void tg_drain_bios(struct throtl_service_queue *parent_sq)
{
	struct throtl_grp *tg;

	while ((tg = throtl_rb_first(parent_sq))) {
		struct throtl_service_queue *sq = &tg->service_queue;
		struct bio *bio;

		throtl_dequeue_tg(tg);

		while ((bio = throtl_peek_queued(&sq->queued[READ])))
			tg_dispatch_one_bio(tg, bio_data_dir(bio));
		while ((bio = throtl_peek_queued(&sq->queued[WRITE])))
			tg_dispatch_one_bio(tg, bio_data_dir(bio));
	}
}