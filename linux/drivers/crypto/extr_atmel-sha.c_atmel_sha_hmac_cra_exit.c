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
struct atmel_sha_hmac_ctx {int /*<<< orphan*/  hkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_sha_hmac_key_release (int /*<<< orphan*/ *) ; 
 struct atmel_sha_hmac_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void atmel_sha_hmac_cra_exit(struct crypto_tfm *tfm)
{
	struct atmel_sha_hmac_ctx *hmac = crypto_tfm_ctx(tfm);

	atmel_sha_hmac_key_release(&hmac->hkey);
}