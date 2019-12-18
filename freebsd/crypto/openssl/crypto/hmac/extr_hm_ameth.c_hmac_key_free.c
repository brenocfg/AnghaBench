#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_1__*) ; 
 TYPE_1__* EVP_PKEY_get0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hmac_key_free(EVP_PKEY *pkey)
{
    ASN1_OCTET_STRING *os = EVP_PKEY_get0(pkey);
    if (os) {
        if (os->data)
            OPENSSL_cleanse(os->data, os->length);
        ASN1_OCTET_STRING_free(os);
    }
}