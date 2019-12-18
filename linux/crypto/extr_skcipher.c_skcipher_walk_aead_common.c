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
struct skcipher_walk {int /*<<< orphan*/  flags; int /*<<< orphan*/  alignmask; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  stride; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  total; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  oiv; int /*<<< orphan*/  iv; scalar_t__ nbytes; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct aead_request {TYPE_1__ base; int /*<<< orphan*/  assoclen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  SKCIPHER_WALK_PHYS ; 
 int /*<<< orphan*/  SKCIPHER_WALK_SLEEP ; 
 int /*<<< orphan*/  crypto_aead_alignmask (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_blocksize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_chunksize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int skcipher_walk_first (struct skcipher_walk*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int skcipher_walk_aead_common(struct skcipher_walk *walk,
				     struct aead_request *req, bool atomic)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	int err;

	walk->nbytes = 0;
	walk->iv = req->iv;
	walk->oiv = req->iv;

	if (unlikely(!walk->total))
		return 0;

	walk->flags &= ~SKCIPHER_WALK_PHYS;

	scatterwalk_start(&walk->in, req->src);
	scatterwalk_start(&walk->out, req->dst);

	scatterwalk_copychunks(NULL, &walk->in, req->assoclen, 2);
	scatterwalk_copychunks(NULL, &walk->out, req->assoclen, 2);

	scatterwalk_done(&walk->in, 0, walk->total);
	scatterwalk_done(&walk->out, 0, walk->total);

	if (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP)
		walk->flags |= SKCIPHER_WALK_SLEEP;
	else
		walk->flags &= ~SKCIPHER_WALK_SLEEP;

	walk->blocksize = crypto_aead_blocksize(tfm);
	walk->stride = crypto_aead_chunksize(tfm);
	walk->ivsize = crypto_aead_ivsize(tfm);
	walk->alignmask = crypto_aead_alignmask(tfm);

	err = skcipher_walk_first(walk);

	if (atomic)
		walk->flags &= ~SKCIPHER_WALK_SLEEP;

	return err;
}