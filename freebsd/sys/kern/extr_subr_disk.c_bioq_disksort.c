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
typedef  scalar_t__ uoff_t ;
struct bio_queue_head {scalar_t__ batched; int /*<<< orphan*/  total; int /*<<< orphan*/  queue; struct bio* insert_point; } ;
struct bio {int bio_flags; scalar_t__ bio_cmd; } ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 
 int BIO_ORDERED ; 
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 struct bio* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct bio*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ) ; 
 struct bio* TAILQ_NEXT (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 
 scalar_t__ bioq_batchsize ; 
 scalar_t__ bioq_bio_key (struct bio_queue_head*,struct bio*) ; 
 int /*<<< orphan*/  bioq_insert_tail (struct bio_queue_head*,struct bio*) ; 

void
bioq_disksort(struct bio_queue_head *head, struct bio *bp)
{
	struct bio *cur, *prev;
	uoff_t key;

	if ((bp->bio_flags & BIO_ORDERED) != 0) {
		/*
		 * Ordered transactions can only be dispatched
		 * after any currently queued transactions.  They
		 * also have barrier semantics - no transactions
		 * queued in the future can pass them.
		 */
		bioq_insert_tail(head, bp);
		return;
	}

	/*
	 * We should only sort requests of types that have concept of offset.
	 * Other types, such as BIO_FLUSH or BIO_ZONE, may imply some degree
	 * of ordering even if strict ordering is not requested explicitly.
	 */
	if (bp->bio_cmd != BIO_READ && bp->bio_cmd != BIO_WRITE &&
	    bp->bio_cmd != BIO_DELETE) {
		bioq_insert_tail(head, bp);
		return;
	}

	if (bioq_batchsize > 0 && head->batched > bioq_batchsize) {
		bioq_insert_tail(head, bp);
		return;
	}

	prev = NULL;
	key = bioq_bio_key(head, bp);
	cur = TAILQ_FIRST(&head->queue);

	if (head->insert_point) {
		prev = head->insert_point;
		cur = TAILQ_NEXT(head->insert_point, bio_queue);
	}

	while (cur != NULL && key >= bioq_bio_key(head, cur)) {
		prev = cur;
		cur = TAILQ_NEXT(cur, bio_queue);
	}

	if (prev == NULL)
		TAILQ_INSERT_HEAD(&head->queue, bp, bio_queue);
	else
		TAILQ_INSERT_AFTER(&head->queue, prev, bp, bio_queue);
	head->total++;
	head->batched++;
}