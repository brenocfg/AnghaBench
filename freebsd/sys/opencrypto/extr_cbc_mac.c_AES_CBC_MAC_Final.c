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
typedef  int uint8_t ;
struct aes_cbc_mac_ctx {scalar_t__ blockIndex; int* staging_block; int* block; int /*<<< orphan*/  rounds; int /*<<< orphan*/  keysched; int /*<<< orphan*/  nonceLength; int /*<<< orphan*/  nonce; int /*<<< orphan*/  cryptDataCount; } ;
typedef  int /*<<< orphan*/  s0 ;

/* Variables and functions */
 size_t AES_CBC_MAC_HASH_LEN ; 
 int CCM_CBC_BLOCK_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  explicit_bzero (int*,int) ; 
 int /*<<< orphan*/  rijndaelEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  xor_and_encrypt (struct aes_cbc_mac_ctx*,int*,int*) ; 

void
AES_CBC_MAC_Final(uint8_t *buf, struct aes_cbc_mac_ctx *ctx)
{
	uint8_t s0[CCM_CBC_BLOCK_LEN];
	
	/*
	 * We first need to check to see if we've got any data
	 * left over to encrypt.
	 */
	if (ctx->blockIndex != 0) {
		xor_and_encrypt(ctx, ctx->staging_block, ctx->block);
		ctx->cryptDataCount += ctx->blockIndex;
		ctx->blockIndex = 0;
		explicit_bzero(ctx->staging_block, sizeof(ctx->staging_block));
	}
	bzero(s0, sizeof(s0));
	s0[0] = (15 - ctx->nonceLength) - 1;
	bcopy(ctx->nonce, s0 + 1, ctx->nonceLength);
	rijndaelEncrypt(ctx->keysched, ctx->rounds, s0, s0);
	for (size_t indx = 0; indx < AES_CBC_MAC_HASH_LEN; indx++)
		buf[indx] = ctx->block[indx] ^ s0[indx];
	explicit_bzero(s0, sizeof(s0));
}