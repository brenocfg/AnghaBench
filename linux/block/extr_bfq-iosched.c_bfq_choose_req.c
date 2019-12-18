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
struct request {int cmd_flags; } ;
struct bfq_data {int bfq_back_max; scalar_t__ bfq_back_penalty; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
#define  BFQ_RQ1_WRAP 129 
#define  BFQ_RQ2_WRAP 128 
 int REQ_META ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ rq_is_sync (struct request*) ; 

__attribute__((used)) static struct request *bfq_choose_req(struct bfq_data *bfqd,
				      struct request *rq1,
				      struct request *rq2,
				      sector_t last)
{
	sector_t s1, s2, d1 = 0, d2 = 0;
	unsigned long back_max;
#define BFQ_RQ1_WRAP	0x01 /* request 1 wraps */
#define BFQ_RQ2_WRAP	0x02 /* request 2 wraps */
	unsigned int wrap = 0; /* bit mask: requests behind the disk head? */

	if (!rq1 || rq1 == rq2)
		return rq2;
	if (!rq2)
		return rq1;

	if (rq_is_sync(rq1) && !rq_is_sync(rq2))
		return rq1;
	else if (rq_is_sync(rq2) && !rq_is_sync(rq1))
		return rq2;
	if ((rq1->cmd_flags & REQ_META) && !(rq2->cmd_flags & REQ_META))
		return rq1;
	else if ((rq2->cmd_flags & REQ_META) && !(rq1->cmd_flags & REQ_META))
		return rq2;

	s1 = blk_rq_pos(rq1);
	s2 = blk_rq_pos(rq2);

	/*
	 * By definition, 1KiB is 2 sectors.
	 */
	back_max = bfqd->bfq_back_max * 2;

	/*
	 * Strict one way elevator _except_ in the case where we allow
	 * short backward seeks which are biased as twice the cost of a
	 * similar forward seek.
	 */
	if (s1 >= last)
		d1 = s1 - last;
	else if (s1 + back_max >= last)
		d1 = (last - s1) * bfqd->bfq_back_penalty;
	else
		wrap |= BFQ_RQ1_WRAP;

	if (s2 >= last)
		d2 = s2 - last;
	else if (s2 + back_max >= last)
		d2 = (last - s2) * bfqd->bfq_back_penalty;
	else
		wrap |= BFQ_RQ2_WRAP;

	/* Found required data */

	/*
	 * By doing switch() on the bit mask "wrap" we avoid having to
	 * check two variables for all permutations: --> faster!
	 */
	switch (wrap) {
	case 0: /* common case for CFQ: rq1 and rq2 not wrapped */
		if (d1 < d2)
			return rq1;
		else if (d2 < d1)
			return rq2;

		if (s1 >= s2)
			return rq1;
		else
			return rq2;

	case BFQ_RQ2_WRAP:
		return rq1;
	case BFQ_RQ1_WRAP:
		return rq2;
	case BFQ_RQ1_WRAP|BFQ_RQ2_WRAP: /* both rqs wrapped */
	default:
		/*
		 * Since both rqs are wrapped,
		 * start with the one that's further behind head
		 * (--> only *one* back seek required),
		 * since back seek takes more time than forward.
		 */
		if (s1 <= s2)
			return rq1;
		else
			return rq2;
	}
}