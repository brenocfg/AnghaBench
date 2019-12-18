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
typedef  int /*<<< orphan*/  u32 ;
struct atmel_aes_gcm_ctx {int /*<<< orphan*/  ghash_resume; int /*<<< orphan*/ * ghash_out; int /*<<< orphan*/  const* ghash_in; } ;
struct atmel_aes_dev {size_t datalen; int /*<<< orphan*/ * data; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  atmel_aes_fn_t ;

/* Variables and functions */
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_gcm_ghash_init ; 
 int atmel_aes_wait_for_data_ready (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_ctrl (struct atmel_aes_dev*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_aes_gcm_ghash(struct atmel_aes_dev *dd,
			       const u32 *data, size_t datalen,
			       const u32 *ghash_in, u32 *ghash_out,
			       atmel_aes_fn_t resume)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);

	dd->data = (u32 *)data;
	dd->datalen = datalen;
	ctx->ghash_in = ghash_in;
	ctx->ghash_out = ghash_out;
	ctx->ghash_resume = resume;

	atmel_aes_write_ctrl(dd, false, NULL);
	return atmel_aes_wait_for_data_ready(dd, atmel_aes_gcm_ghash_init);
}