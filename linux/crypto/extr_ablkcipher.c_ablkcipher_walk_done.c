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
struct TYPE_4__ {int /*<<< orphan*/  ivsize; } ;
struct crypto_tfm {TYPE_2__ crt_ablkcipher; } ;
struct ablkcipher_walk {int nbytes; scalar_t__ total; int flags; scalar_t__ iv; int /*<<< orphan*/  iv_buffer; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; struct crypto_tfm* tfm; } ;
struct ablkcipher_request {scalar_t__ info; TYPE_1__ base; } ;

/* Variables and functions */
 int ABLKCIPHER_WALK_SLOW ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ablkcipher_done_fast (struct ablkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  ablkcipher_done_slow (struct ablkcipher_walk*,unsigned int) ; 
 int ablkcipher_walk_next (struct ablkcipher_request*,struct ablkcipher_walk*) ; 
 int /*<<< orphan*/  crypto_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_done (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ablkcipher_walk_done(struct ablkcipher_request *req,
			 struct ablkcipher_walk *walk, int err)
{
	struct crypto_tfm *tfm = req->base.tfm;
	unsigned int n; /* bytes processed */
	bool more;

	if (unlikely(err < 0))
		goto finish;

	n = walk->nbytes - err;
	walk->total -= n;
	more = (walk->total != 0);

	if (likely(!(walk->flags & ABLKCIPHER_WALK_SLOW))) {
		ablkcipher_done_fast(walk, n);
	} else {
		if (WARN_ON(err)) {
			/* unexpected case; didn't process all bytes */
			err = -EINVAL;
			goto finish;
		}
		ablkcipher_done_slow(walk, n);
	}

	scatterwalk_done(&walk->in, 0, more);
	scatterwalk_done(&walk->out, 1, more);

	if (more) {
		crypto_yield(req->base.flags);
		return ablkcipher_walk_next(req, walk);
	}
	err = 0;
finish:
	walk->nbytes = 0;
	if (walk->iv != req->info)
		memcpy(req->info, walk->iv, tfm->crt_ablkcipher.ivsize);
	kfree(walk->iv_buffer);
	return err;
}