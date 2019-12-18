#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int auth_input_type; int /*<<< orphan*/  iv_source; int /*<<< orphan*/  hash_type; int /*<<< orphan*/  cipher_type; } ;
union fc_ctx_flags {int /*<<< orphan*/  f; TYPE_1__ w0; } ;
struct TYPE_6__ {TYPE_2__* fctx; } ;
struct nitrox_crypto_ctx {TYPE_3__ u; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_5__ {union fc_ctx_flags flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_NULL ; 
 int /*<<< orphan*/  CIPHER_AES_GCM ; 
 int /*<<< orphan*/  IV_FROM_DPTR ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct nitrox_crypto_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int nitrox_aead_init (struct crypto_aead*) ; 

__attribute__((used)) static int nitrox_gcm_common_init(struct crypto_aead *aead)
{
	int ret;
	struct nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	union fc_ctx_flags *flags;

	ret = nitrox_aead_init(aead);
	if (ret)
		return ret;

	flags = &nctx->u.fctx->flags;
	flags->w0.cipher_type = CIPHER_AES_GCM;
	flags->w0.hash_type = AUTH_NULL;
	flags->w0.iv_source = IV_FROM_DPTR;
	/* ask microcode to calculate ipad/opad */
	flags->w0.auth_input_type = 1;
	flags->f = be64_to_cpu(flags->f);

	return 0;
}