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
struct ablk_ctx {scalar_t__ ciph_mode; int enckey_len; scalar_t__ rrkey; scalar_t__ key; } ;
struct _key_ctx {scalar_t__ key; } ;

/* Variables and functions */
 scalar_t__ CHCR_SCMD_CIPHER_MODE_AES_CBC ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int generate_copy_rrkey(struct ablk_ctx *ablkctx,
			       struct _key_ctx *key_ctx)
{
	if (ablkctx->ciph_mode == CHCR_SCMD_CIPHER_MODE_AES_CBC) {
		memcpy(key_ctx->key, ablkctx->rrkey, ablkctx->enckey_len);
	} else {
		memcpy(key_ctx->key,
		       ablkctx->key + (ablkctx->enckey_len >> 1),
		       ablkctx->enckey_len >> 1);
		memcpy(key_ctx->key + (ablkctx->enckey_len >> 1),
		       ablkctx->rrkey, ablkctx->enckey_len >> 1);
	}
	return 0;
}