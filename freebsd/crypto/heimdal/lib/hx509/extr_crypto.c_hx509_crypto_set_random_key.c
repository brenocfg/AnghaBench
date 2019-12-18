#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_crypto ;
typedef  int /*<<< orphan*/  heim_octet_string ;
struct TYPE_5__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_3__ key; int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ EVP_CIPHER_key_length (int /*<<< orphan*/ ) ; 
 int HX509_CRYPTO_INTERNAL_ERROR ; 
 scalar_t__ RAND_bytes (int /*<<< orphan*/ *,scalar_t__) ; 
 int der_copy_octet_string (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 

int
hx509_crypto_set_random_key(hx509_crypto crypto, heim_octet_string *key)
{
    if (crypto->key.data) {
	free(crypto->key.data);
	crypto->key.length = 0;
    }

    crypto->key.length = EVP_CIPHER_key_length(crypto->c);
    crypto->key.data = malloc(crypto->key.length);
    if (crypto->key.data == NULL) {
	crypto->key.length = 0;
	return ENOMEM;
    }
    if (RAND_bytes(crypto->key.data, crypto->key.length) <= 0) {
	free(crypto->key.data);
	crypto->key.data = NULL;
	crypto->key.length = 0;
	return HX509_CRYPTO_INTERNAL_ERROR;
    }
    if (key)
	return der_copy_octet_string(&crypto->key, key);
    else
	return 0;
}