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
struct crypto_cipher {int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 scalar_t__ GPG_ERR_NO_ERROR ; 
 scalar_t__ gcry_cipher_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,size_t) ; 

int crypto_cipher_encrypt(struct crypto_cipher *ctx, const u8 *plain,
			  u8 *crypt, size_t len)
{
	if (gcry_cipher_encrypt(ctx->enc, crypt, len, plain, len) !=
	    GPG_ERR_NO_ERROR)
		return -1;
	return 0;
}