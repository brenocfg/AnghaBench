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
struct aes_icm_ctx {int /*<<< orphan*/  ac_block; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AESICM_BLOCKSIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aes_icm_reinit(caddr_t key, const u_int8_t *iv)
{
	struct aes_icm_ctx *ctx;

	ctx = (struct aes_icm_ctx *)key;
	bcopy(iv, ctx->ac_block, AESICM_BLOCKSIZE);
}