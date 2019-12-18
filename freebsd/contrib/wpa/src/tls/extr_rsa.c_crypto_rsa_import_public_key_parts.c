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
struct crypto_rsa_key {int /*<<< orphan*/ * e; int /*<<< orphan*/ * n; } ;

/* Variables and functions */
 void* bignum_init () ; 
 scalar_t__ bignum_set_unsigned_bin (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  crypto_rsa_free (struct crypto_rsa_key*) ; 
 struct crypto_rsa_key* os_zalloc (int) ; 

struct crypto_rsa_key *
crypto_rsa_import_public_key_parts(const u8 *n, size_t n_len,
				   const u8 *e, size_t e_len)
{
	struct crypto_rsa_key *key;

	key = os_zalloc(sizeof(*key));
	if (key == NULL)
		return NULL;

	key->n = bignum_init();
	key->e = bignum_init();
	if (key->n == NULL || key->e == NULL ||
	    bignum_set_unsigned_bin(key->n, n, n_len) < 0 ||
	    bignum_set_unsigned_bin(key->e, e, e_len) < 0) {
		crypto_rsa_free(key);
		return NULL;
	}

	return key;
}