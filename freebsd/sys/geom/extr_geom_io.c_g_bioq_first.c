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
struct g_bioq {int /*<<< orphan*/  bio_queue_length; int /*<<< orphan*/  bio_queue; } ;
struct bio {int bio_flags; } ;

/* Variables and functions */
 int BIO_ONQUEUE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct bio* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 

__attribute__((used)) static struct bio *
g_bioq_first(struct g_bioq *bq)
{
	struct bio *bp;

	bp = TAILQ_FIRST(&bq->bio_queue);
	if (bp != NULL) {
		KASSERT((bp->bio_flags & BIO_ONQUEUE),
		    ("Bio not on queue bp=%p target %p", bp, bq));
		bp->bio_flags &= ~BIO_ONQUEUE;
		TAILQ_REMOVE(&bq->bio_queue, bp, bio_queue);
		bq->bio_queue_length--;
	}
	return (bp);
}