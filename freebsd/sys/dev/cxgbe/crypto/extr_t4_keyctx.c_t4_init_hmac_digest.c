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
typedef  union authctx {int dummy; } authctx ;
typedef  size_t u_int ;
struct auth_hash {int blocksize; int hashsize; int /*<<< orphan*/  type; int /*<<< orphan*/  (* Update ) (union authctx*,char*,int) ;int /*<<< orphan*/  (* Init ) (union authctx*) ;int /*<<< orphan*/  (* Final ) (char*,union authctx*) ;} ;

/* Variables and functions */
 char HMAC_IPAD_VAL ; 
 char HMAC_OPAD_VAL ; 
 int SHA2_512_BLOCK_LEN ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roundup2 (size_t,int) ; 
 int /*<<< orphan*/  stub1 (union authctx*) ; 
 int /*<<< orphan*/  stub2 (union authctx*,char*,int) ; 
 int /*<<< orphan*/  stub3 (char*,union authctx*) ; 
 int /*<<< orphan*/  stub4 (union authctx*) ; 
 int /*<<< orphan*/  stub5 (union authctx*,char*,int) ; 
 int /*<<< orphan*/  stub6 (union authctx*) ; 
 int /*<<< orphan*/  stub7 (union authctx*,char*,int) ; 
 int /*<<< orphan*/  t4_copy_partial_hash (int /*<<< orphan*/ ,union authctx*,char*) ; 

void
t4_init_hmac_digest(struct auth_hash *axf, u_int partial_digest_len,
    char *key, int klen, char *dst)
{
	union authctx auth_ctx;
	char ipad[SHA2_512_BLOCK_LEN], opad[SHA2_512_BLOCK_LEN];
	u_int i;

	/*
	 * If the key is larger than the block size, use the digest of
	 * the key as the key instead.
	 */
	klen /= 8;
	if (klen > axf->blocksize) {
		axf->Init(&auth_ctx);
		axf->Update(&auth_ctx, key, klen);
		axf->Final(ipad, &auth_ctx);
		klen = axf->hashsize;
	} else
		memcpy(ipad, key, klen);

	memset(ipad + klen, 0, axf->blocksize - klen);
	memcpy(opad, ipad, axf->blocksize);

	for (i = 0; i < axf->blocksize; i++) {
		ipad[i] ^= HMAC_IPAD_VAL;
		opad[i] ^= HMAC_OPAD_VAL;
	}

	/*
	 * Hash the raw ipad and opad and store the partial results in
	 * the key context.
	 */
	axf->Init(&auth_ctx);
	axf->Update(&auth_ctx, ipad, axf->blocksize);
	t4_copy_partial_hash(axf->type, &auth_ctx, dst);

	dst += roundup2(partial_digest_len, 16);
	axf->Init(&auth_ctx);
	axf->Update(&auth_ctx, opad, axf->blocksize);
	t4_copy_partial_hash(axf->type, &auth_ctx, dst);
}