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
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NX_FC_AES ; 
 int /*<<< orphan*/  NX_MODE_AES_CBC ; 
 int /*<<< orphan*/  crypto_tfm_ctx (struct crypto_tfm*) ; 
 int nx_crypto_ctx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nx_crypto_ctx_aes_cbc_init(struct crypto_tfm *tfm)
{
	return nx_crypto_ctx_init(crypto_tfm_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_CBC);
}