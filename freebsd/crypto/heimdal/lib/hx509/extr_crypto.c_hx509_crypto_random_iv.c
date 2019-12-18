#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_crypto ;
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ heim_octet_string ;
struct TYPE_5__ {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ EVP_CIPHER_iv_length (int /*<<< orphan*/ ) ; 
 int HX509_CRYPTO_INTERNAL_ERROR ; 
 scalar_t__ RAND_bytes (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 

int
hx509_crypto_random_iv(hx509_crypto crypto, heim_octet_string *ivec)
{
    ivec->length = EVP_CIPHER_iv_length(crypto->c);
    ivec->data = malloc(ivec->length);
    if (ivec->data == NULL) {
	ivec->length = 0;
	return ENOMEM;
    }

    if (RAND_bytes(ivec->data, ivec->length) <= 0) {
	free(ivec->data);
	ivec->data = NULL;
	ivec->length = 0;
	return HX509_CRYPTO_INTERNAL_ERROR;
    }
    return 0;
}