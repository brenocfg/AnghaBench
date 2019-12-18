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
struct atmel_aes_gcm_ctx {scalar_t__ ghash_in; } ;
struct atmel_aes_dev {int /*<<< orphan*/  total; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_AADLENR ; 
 int /*<<< orphan*/  AES_CLENR ; 
 int /*<<< orphan*/  AES_GHASHR (int /*<<< orphan*/ ) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_gcm_ghash_finalize (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_write (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atmel_aes_gcm_ghash_init(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);

	/* Set the data length. */
	atmel_aes_write(dd, AES_AADLENR, dd->total);
	atmel_aes_write(dd, AES_CLENR, 0);

	/* If needed, overwrite the GCM Intermediate Hash Word Registers */
	if (ctx->ghash_in)
		atmel_aes_write_block(dd, AES_GHASHR(0), ctx->ghash_in);

	return atmel_aes_gcm_ghash_finalize(dd);
}