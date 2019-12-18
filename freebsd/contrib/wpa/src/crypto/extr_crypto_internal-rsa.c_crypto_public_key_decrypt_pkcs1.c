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
struct crypto_rsa_key {int dummy; } ;
struct crypto_public_key {int dummy; } ;

/* Variables and functions */
 int pkcs1_decrypt_public_key (struct crypto_rsa_key*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 

int crypto_public_key_decrypt_pkcs1(struct crypto_public_key *key,
				    const u8 *crypt, size_t crypt_len,
				    u8 *plain, size_t *plain_len)
{
	return pkcs1_decrypt_public_key((struct crypto_rsa_key *) key,
					crypt, crypt_len, plain, plain_len);
}