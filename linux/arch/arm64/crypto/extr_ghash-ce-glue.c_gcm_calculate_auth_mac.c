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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct scatter_walk {int /*<<< orphan*/  sg; } ;
struct gcm_aes_ctx {int /*<<< orphan*/  ghash_key; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  src; scalar_t__ assoclen; } ;

/* Variables and functions */
 int GHASH_BLOCK_SIZE ; 
 struct gcm_aes_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  gcm_update_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int*,struct gcm_aes_ctx*) ; 
 int /*<<< orphan*/  ghash_do_update (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmull_ghash_update_p64 ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,scalar_t__) ; 
 scalar_t__ scatterwalk_clamp (struct scatter_walk*,scalar_t__) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * scatterwalk_map (struct scatter_walk*) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gcm_calculate_auth_mac(struct aead_request *req, u64 dg[])
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct gcm_aes_ctx *ctx = crypto_aead_ctx(aead);
	u8 buf[GHASH_BLOCK_SIZE];
	struct scatter_walk walk;
	u32 len = req->assoclen;
	int buf_count = 0;

	scatterwalk_start(&walk, req->src);

	do {
		u32 n = scatterwalk_clamp(&walk, len);
		u8 *p;

		if (!n) {
			scatterwalk_start(&walk, sg_next(walk.sg));
			n = scatterwalk_clamp(&walk, len);
		}
		p = scatterwalk_map(&walk);

		gcm_update_mac(dg, p, n, buf, &buf_count, ctx);
		len -= n;

		scatterwalk_unmap(p);
		scatterwalk_advance(&walk, n);
		scatterwalk_done(&walk, 0, len);
	} while (len);

	if (buf_count) {
		memset(&buf[buf_count], 0, GHASH_BLOCK_SIZE - buf_count);
		ghash_do_update(1, dg, buf, &ctx->ghash_key, NULL,
				pmull_ghash_update_p64);
	}
}