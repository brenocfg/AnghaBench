#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {int rq_flags; } ;
struct TYPE_2__ {scalar_t__ bi_size; } ;
struct bio {TYPE_1__ bi_iter; scalar_t__ bi_status; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_QUIET ; 
 int RQF_FLUSH_SEQ ; 
 int RQF_QUIET ; 
 int /*<<< orphan*/  bio_advance (struct bio*,unsigned int) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void req_bio_endio(struct request *rq, struct bio *bio,
			  unsigned int nbytes, blk_status_t error)
{
	if (error)
		bio->bi_status = error;

	if (unlikely(rq->rq_flags & RQF_QUIET))
		bio_set_flag(bio, BIO_QUIET);

	bio_advance(bio, nbytes);

	/* don't actually finish bio if it's part of flush sequence */
	if (bio->bi_iter.bi_size == 0 && !(rq->rq_flags & RQF_FLUSH_SEQ))
		bio_endio(bio);
}