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
struct skcipher_request {int cryptlen; } ;
struct rctx {struct skcipher_request subreq; } ;

/* Variables and functions */
 int XTS_BLOCK_SIZE ; 
 scalar_t__ crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int cts_final (struct skcipher_request*,scalar_t__ (*) (struct skcipher_request*)) ; 
 int /*<<< orphan*/  encrypt_done ; 
 scalar_t__ init_crypt (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int xor_tweak_post (struct skcipher_request*,int) ; 
 scalar_t__ xor_tweak_pre (struct skcipher_request*,int) ; 

__attribute__((used)) static int encrypt(struct skcipher_request *req)
{
	struct rctx *rctx = skcipher_request_ctx(req);
	struct skcipher_request *subreq = &rctx->subreq;
	int err;

	err = init_crypt(req, encrypt_done) ?:
	      xor_tweak_pre(req, true) ?:
	      crypto_skcipher_encrypt(subreq) ?:
	      xor_tweak_post(req, true);

	if (err || likely((req->cryptlen % XTS_BLOCK_SIZE) == 0))
		return err;

	return cts_final(req, crypto_skcipher_encrypt);
}