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
struct aes_icm_ctx {int* ac_block; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int AESICM_BLOCKSIZE ; 
 int AES_CCM_IV_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int*,int) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 

__attribute__((used)) static void
aes_ccm_reinit(caddr_t key, const u_int8_t *iv)
{
	struct aes_icm_ctx *ctx;

	ctx = (struct aes_icm_ctx*)key;

	/* CCM has flags, then the IV, then the counter, which starts at 1 */
	bzero(ctx->ac_block, sizeof(ctx->ac_block));
	/* 3 bytes for length field; this gives a nonce of 12 bytes */
	ctx->ac_block[0] = (15 - AES_CCM_IV_LEN) - 1;
	bcopy(iv, ctx->ac_block+1, AES_CCM_IV_LEN);
	ctx->ac_block[AESICM_BLOCKSIZE - 1] = 1;
}