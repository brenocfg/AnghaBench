#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ addr; } ;
struct TYPE_4__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; unsigned int total; int flags; scalar_t__ page; scalar_t__ buffer; scalar_t__ iv; scalar_t__ oiv; unsigned int ivsize; int /*<<< orphan*/  out; int /*<<< orphan*/  in; TYPE_2__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int SKCIPHER_WALK_COPY ; 
 int SKCIPHER_WALK_DIFF ; 
 int SKCIPHER_WALK_PHYS ; 
 int SKCIPHER_WALK_SLEEP ; 
 int SKCIPHER_WALK_SLOW ; 
 int /*<<< orphan*/  crypto_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_advance (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (int /*<<< orphan*/ *,int,unsigned int) ; 
 unsigned int skcipher_done_slow (struct skcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  skcipher_map_dst (struct skcipher_walk*) ; 
 int /*<<< orphan*/  skcipher_unmap_dst (struct skcipher_walk*) ; 
 int /*<<< orphan*/  skcipher_unmap_src (struct skcipher_walk*) ; 
 int skcipher_walk_next (struct skcipher_walk*) ; 
 scalar_t__ unlikely (int) ; 

int skcipher_walk_done(struct skcipher_walk *walk, int err)
{
	unsigned int n = walk->nbytes;
	unsigned int nbytes = 0;

	if (!n)
		goto finish;

	if (likely(err >= 0)) {
		n -= err;
		nbytes = walk->total - n;
	}

	if (likely(!(walk->flags & (SKCIPHER_WALK_PHYS |
				    SKCIPHER_WALK_SLOW |
				    SKCIPHER_WALK_COPY |
				    SKCIPHER_WALK_DIFF)))) {
unmap_src:
		skcipher_unmap_src(walk);
	} else if (walk->flags & SKCIPHER_WALK_DIFF) {
		skcipher_unmap_dst(walk);
		goto unmap_src;
	} else if (walk->flags & SKCIPHER_WALK_COPY) {
		skcipher_map_dst(walk);
		memcpy(walk->dst.virt.addr, walk->page, n);
		skcipher_unmap_dst(walk);
	} else if (unlikely(walk->flags & SKCIPHER_WALK_SLOW)) {
		if (err > 0) {
			/*
			 * Didn't process all bytes.  Either the algorithm is
			 * broken, or this was the last step and it turned out
			 * the message wasn't evenly divisible into blocks but
			 * the algorithm requires it.
			 */
			err = -EINVAL;
			nbytes = 0;
		} else
			n = skcipher_done_slow(walk, n);
	}

	if (err > 0)
		err = 0;

	walk->total = nbytes;
	walk->nbytes = 0;

	scatterwalk_advance(&walk->in, n);
	scatterwalk_advance(&walk->out, n);
	scatterwalk_done(&walk->in, 0, nbytes);
	scatterwalk_done(&walk->out, 1, nbytes);

	if (nbytes) {
		crypto_yield(walk->flags & SKCIPHER_WALK_SLEEP ?
			     CRYPTO_TFM_REQ_MAY_SLEEP : 0);
		return skcipher_walk_next(walk);
	}

finish:
	/* Short-circuit for the common/fast path. */
	if (!((unsigned long)walk->buffer | (unsigned long)walk->page))
		goto out;

	if (walk->flags & SKCIPHER_WALK_PHYS)
		goto out;

	if (walk->iv != walk->oiv)
		memcpy(walk->oiv, walk->iv, walk->ivsize);
	if (walk->buffer != walk->page)
		kfree(walk->buffer);
	if (walk->page)
		free_page((unsigned long)walk->page);

out:
	return err;
}