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
struct chachapoly_req_ctx {int /*<<< orphan*/  flags; scalar_t__ cryptlen; } ;
struct aead_request {scalar_t__ cryptlen; } ;

/* Variables and functions */
 scalar_t__ POLY1305_DIGEST_SIZE ; 
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int poly_genkey (struct aead_request*) ; 

__attribute__((used)) static int chachapoly_decrypt(struct aead_request *req)
{
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);

	rctx->cryptlen = req->cryptlen - POLY1305_DIGEST_SIZE;
	rctx->flags = aead_request_flags(req);

	/* decrypt call chain:
	 * - poly_genkey/done()
	 * - poly_init/done()
	 * - poly_setkey/done()
	 * - poly_ad/done()
	 * - poly_adpad/done()
	 * - poly_cipher/done()
	 * - poly_cipherpad/done()
	 * - poly_tail/done/continue()
	 * - chacha_decrypt/done()
	 * - poly_verify_tag()
	 */
	return poly_genkey(req);
}