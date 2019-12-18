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
struct nx_gcm_rctx {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NX_FC_AES ; 
 int /*<<< orphan*/  NX_MODE_AES_GCM ; 
 int /*<<< orphan*/  crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int) ; 
 int nx_crypto_ctx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nx_crypto_ctx_aes_gcm_init(struct crypto_aead *tfm)
{
	crypto_aead_set_reqsize(tfm, sizeof(struct nx_gcm_rctx));
	return nx_crypto_ctx_init(crypto_aead_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_GCM);
}