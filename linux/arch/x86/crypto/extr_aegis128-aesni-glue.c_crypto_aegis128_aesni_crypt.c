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
struct skcipher_walk {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aegis_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes; } ;
struct aegis_ctx {TYPE_1__ key; } ;
struct aegis_crypt_ops {int /*<<< orphan*/  (* skcipher_walk_init ) (struct skcipher_walk*,struct aead_request*,int) ;} ;
struct aegis_block {int dummy; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct aegis_ctx* crypto_aegis128_aesni_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aegis128_aesni_final (struct aegis_state*,struct aegis_block*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_aegis128_aesni_init (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aegis128_aesni_process_ad (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aegis128_aesni_process_crypt (struct aegis_state*,struct skcipher_walk*,struct aegis_crypt_ops const*) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int /*<<< orphan*/  stub1 (struct skcipher_walk*,struct aead_request*,int) ; 

__attribute__((used)) static void crypto_aegis128_aesni_crypt(struct aead_request *req,
					struct aegis_block *tag_xor,
					unsigned int cryptlen,
					const struct aegis_crypt_ops *ops)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct aegis_ctx *ctx = crypto_aegis128_aesni_ctx(tfm);
	struct skcipher_walk walk;
	struct aegis_state state;

	ops->skcipher_walk_init(&walk, req, true);

	kernel_fpu_begin();

	crypto_aegis128_aesni_init(&state, ctx->key.bytes, req->iv);
	crypto_aegis128_aesni_process_ad(&state, req->src, req->assoclen);
	crypto_aegis128_aesni_process_crypt(&state, &walk, ops);
	crypto_aegis128_aesni_final(&state, tag_xor, req->assoclen, cryptlen);

	kernel_fpu_end();
}