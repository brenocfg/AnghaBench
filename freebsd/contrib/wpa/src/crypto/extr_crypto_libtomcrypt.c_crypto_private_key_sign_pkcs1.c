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
struct crypto_private_key {int /*<<< orphan*/  rsa; } ;

/* Variables and functions */
 int /*<<< orphan*/  PK_PRIVATE ; 
 int crypto_rsa_encrypt_pkcs1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 

int crypto_private_key_sign_pkcs1(struct crypto_private_key *key,
				  const u8 *in, size_t inlen,
				  u8 *out, size_t *outlen)
{
	return crypto_rsa_encrypt_pkcs1(1, &key->rsa, PK_PRIVATE, in, inlen,
					out, outlen);
}