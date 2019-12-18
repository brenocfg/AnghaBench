#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_crypto ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {TYPE_1__ key; int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EVP_CIPHER_key_length (int /*<<< orphan*/ ) ; 
 int HX509_CRYPTO_INTERNAL_ERROR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

int
hx509_crypto_set_key_data(hx509_crypto crypto, const void *data, size_t length)
{
    if (EVP_CIPHER_key_length(crypto->c) > (int)length)
	return HX509_CRYPTO_INTERNAL_ERROR;

    if (crypto->key.data) {
	free(crypto->key.data);
	crypto->key.data = NULL;
	crypto->key.length = 0;
    }
    crypto->key.data = malloc(length);
    if (crypto->key.data == NULL)
	return ENOMEM;
    memcpy(crypto->key.data, data, length);
    crypto->key.length = length;

    return 0;
}