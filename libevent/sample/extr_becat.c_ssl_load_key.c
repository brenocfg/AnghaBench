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
struct ssl_context {int /*<<< orphan*/  pkey; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_assign_RSA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_new () ; 
 int /*<<< orphan*/  RSA_F4 ; 
 int RSA_generate_key_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 

__attribute__((used)) static int ssl_load_key(struct ssl_context *ssl)
{
	int err = 1;
	BIGNUM *bn;
	RSA *key;

	ssl->pkey = EVP_PKEY_new();

	bn = BN_new();
	if (BN_set_word(bn, RSA_F4) != 1)
		goto err;
	/** Will be freed with ctx.pkey */
	key = RSA_new();
	if (RSA_generate_key_ex(key, 2048, bn, NULL) != 1)
		goto err;
	if (EVP_PKEY_assign_RSA(ssl->pkey, key) != 1)
		goto err;
	err = 0;
err:
	BN_free(bn);
	return err;
}