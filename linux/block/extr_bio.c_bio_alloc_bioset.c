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
struct bio_vec {int dummy; } ;
struct bio_set {unsigned int front_pad; int /*<<< orphan*/  bio_pool; int /*<<< orphan*/  bvec_pool; scalar_t__ rescue_workqueue; } ;
struct bio {unsigned long bi_flags; unsigned int bi_max_vecs; struct bio_vec* bi_io_vec; struct bio_set* bi_pool; struct bio_vec* bi_inline_vecs; } ;
typedef  scalar_t__ gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/ * bio_list; } ;

/* Variables and functions */
 unsigned int BIO_INLINE_VECS ; 
 unsigned long BVEC_POOL_OFFSET ; 
 unsigned int UIO_MAXIOV ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ __GFP_DIRECT_RECLAIM ; 
 int /*<<< orphan*/  bio_init (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_empty (int /*<<< orphan*/ *) ; 
 struct bio_vec* bvec_alloc (scalar_t__,unsigned int,unsigned long*,int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 void* kmalloc (int,scalar_t__) ; 
 void* mempool_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mempool_free (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  punt_bios_to_rescuer (struct bio_set*) ; 
 scalar_t__ unlikely (int) ; 

struct bio *bio_alloc_bioset(gfp_t gfp_mask, unsigned int nr_iovecs,
			     struct bio_set *bs)
{
	gfp_t saved_gfp = gfp_mask;
	unsigned front_pad;
	unsigned inline_vecs;
	struct bio_vec *bvl = NULL;
	struct bio *bio;
	void *p;

	if (!bs) {
		if (nr_iovecs > UIO_MAXIOV)
			return NULL;

		p = kmalloc(sizeof(struct bio) +
			    nr_iovecs * sizeof(struct bio_vec),
			    gfp_mask);
		front_pad = 0;
		inline_vecs = nr_iovecs;
	} else {
		/* should not use nobvec bioset for nr_iovecs > 0 */
		if (WARN_ON_ONCE(!mempool_initialized(&bs->bvec_pool) &&
				 nr_iovecs > 0))
			return NULL;
		/*
		 * generic_make_request() converts recursion to iteration; this
		 * means if we're running beneath it, any bios we allocate and
		 * submit will not be submitted (and thus freed) until after we
		 * return.
		 *
		 * This exposes us to a potential deadlock if we allocate
		 * multiple bios from the same bio_set() while running
		 * underneath generic_make_request(). If we were to allocate
		 * multiple bios (say a stacking block driver that was splitting
		 * bios), we would deadlock if we exhausted the mempool's
		 * reserve.
		 *
		 * We solve this, and guarantee forward progress, with a rescuer
		 * workqueue per bio_set. If we go to allocate and there are
		 * bios on current->bio_list, we first try the allocation
		 * without __GFP_DIRECT_RECLAIM; if that fails, we punt those
		 * bios we would be blocking to the rescuer workqueue before
		 * we retry with the original gfp_flags.
		 */

		if (current->bio_list &&
		    (!bio_list_empty(&current->bio_list[0]) ||
		     !bio_list_empty(&current->bio_list[1])) &&
		    bs->rescue_workqueue)
			gfp_mask &= ~__GFP_DIRECT_RECLAIM;

		p = mempool_alloc(&bs->bio_pool, gfp_mask);
		if (!p && gfp_mask != saved_gfp) {
			punt_bios_to_rescuer(bs);
			gfp_mask = saved_gfp;
			p = mempool_alloc(&bs->bio_pool, gfp_mask);
		}

		front_pad = bs->front_pad;
		inline_vecs = BIO_INLINE_VECS;
	}

	if (unlikely(!p))
		return NULL;

	bio = p + front_pad;
	bio_init(bio, NULL, 0);

	if (nr_iovecs > inline_vecs) {
		unsigned long idx = 0;

		bvl = bvec_alloc(gfp_mask, nr_iovecs, &idx, &bs->bvec_pool);
		if (!bvl && gfp_mask != saved_gfp) {
			punt_bios_to_rescuer(bs);
			gfp_mask = saved_gfp;
			bvl = bvec_alloc(gfp_mask, nr_iovecs, &idx, &bs->bvec_pool);
		}

		if (unlikely(!bvl))
			goto err_free;

		bio->bi_flags |= idx << BVEC_POOL_OFFSET;
	} else if (nr_iovecs) {
		bvl = bio->bi_inline_vecs;
	}

	bio->bi_pool = bs;
	bio->bi_max_vecs = nr_iovecs;
	bio->bi_io_vec = bvl;
	return bio;

err_free:
	mempool_free(p, &bs->bio_pool);
	return NULL;
}