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
struct aes_icm_ctx {scalar_t__* ac_block; int /*<<< orphan*/  ac_nr; int /*<<< orphan*/  ac_ek; } ;
typedef  int /*<<< orphan*/  keystream ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int AESICM_BLOCKSIZE ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rijndaelEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aes_icm_crypt(caddr_t key, u_int8_t *data)
{
	struct aes_icm_ctx *ctx;
	u_int8_t keystream[AESICM_BLOCKSIZE];
	int i;

	ctx = (struct aes_icm_ctx *)key;
	rijndaelEncrypt(ctx->ac_ek, ctx->ac_nr, ctx->ac_block, keystream);
	for (i = 0; i < AESICM_BLOCKSIZE; i++)
		data[i] ^= keystream[i];
	explicit_bzero(keystream, sizeof(keystream));

	/* increment counter */
	for (i = AESICM_BLOCKSIZE - 1;
	     i >= 0; i--)
		if (++ctx->ac_block[i])   /* continue on overflow */
			break;
}