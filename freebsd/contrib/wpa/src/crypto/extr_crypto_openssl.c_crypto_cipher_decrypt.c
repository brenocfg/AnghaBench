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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_cipher {int /*<<< orphan*/  dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DecryptUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/  const*,size_t) ; 

int crypto_cipher_decrypt(struct crypto_cipher *ctx, const u8 *crypt,
			  u8 *plain, size_t len)
{
	int outl;
	outl = len;
	if (!EVP_DecryptUpdate(ctx->dec, plain, &outl, crypt, len))
		return -1;
	return 0;
}