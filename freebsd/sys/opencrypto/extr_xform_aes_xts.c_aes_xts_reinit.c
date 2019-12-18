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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int64_t ;
typedef  size_t u_int ;
struct aes_xts_ctx {int* tweak; int /*<<< orphan*/  key2; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 size_t AES_XTS_IVSIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int*,size_t) ; 
 int /*<<< orphan*/  bzero (int*,size_t) ; 
 int /*<<< orphan*/  rijndael_encrypt (int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static void
aes_xts_reinit(caddr_t key, const u_int8_t *iv)
{
	struct aes_xts_ctx *ctx = (struct aes_xts_ctx *)key;
	u_int64_t blocknum;
	u_int i;

	/*
	 * Prepare tweak as E_k2(IV). IV is specified as LE representation
	 * of a 64-bit block number which we allow to be passed in directly.
	 */
	bcopy(iv, &blocknum, AES_XTS_IVSIZE);
	for (i = 0; i < AES_XTS_IVSIZE; i++) {
		ctx->tweak[i] = blocknum & 0xff;
		blocknum >>= 8;
	}
	/* Last 64 bits of IV are always zero */
	bzero(ctx->tweak + AES_XTS_IVSIZE, AES_XTS_IVSIZE);

	rijndael_encrypt(&ctx->key2, ctx->tweak, ctx->tweak);
}