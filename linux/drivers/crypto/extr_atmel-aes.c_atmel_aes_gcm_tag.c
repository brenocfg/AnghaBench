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
struct atmel_aes_gcm_ctx {int /*<<< orphan*/  ghash; int /*<<< orphan*/  j0; } ;
struct atmel_aes_dev {unsigned long flags; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int AES_FLAGS_CTR ; 
 int AES_FLAGS_GTAGEN ; 
 int AES_FLAGS_OPMODE_MASK ; 
 int /*<<< orphan*/  AES_IDATAR (int /*<<< orphan*/ ) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_gcm_finalize ; 
 int atmel_aes_wait_for_data_ready (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_ctrl (struct atmel_aes_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_aes_gcm_tag(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	unsigned long flags;

	/*
	 * Change mode to CTR to complete the tag generation.
	 * Use J0 as Initialization Vector.
	 */
	flags = dd->flags;
	dd->flags &= ~(AES_FLAGS_OPMODE_MASK | AES_FLAGS_GTAGEN);
	dd->flags |= AES_FLAGS_CTR;
	atmel_aes_write_ctrl(dd, false, ctx->j0);
	dd->flags = flags;

	atmel_aes_write_block(dd, AES_IDATAR(0), ctx->ghash);
	return atmel_aes_wait_for_data_ready(dd, atmel_aes_gcm_finalize);
}