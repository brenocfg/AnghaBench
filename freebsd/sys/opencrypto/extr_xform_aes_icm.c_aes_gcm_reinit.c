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
 int /*<<< orphan*/  aes_icm_reinit (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 

__attribute__((used)) static void
aes_gcm_reinit(caddr_t key, const u_int8_t *iv)
{
	struct aes_icm_ctx *ctx;

	aes_icm_reinit(key, iv);

	ctx = (struct aes_icm_ctx *)key;
	/* GCM starts with 2 as counter 1 is used for final xor of tag. */
	bzero(&ctx->ac_block[AESICM_BLOCKSIZE - 4], 4);
	ctx->ac_block[AESICM_BLOCKSIZE - 1] = 2;
}