#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * enc_pkey; int /*<<< orphan*/ * enc_algor; } ;
typedef  TYPE_1__ X509_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_X509_PKEY_NEW ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/ * X509_ALGOR_new () ; 
 int /*<<< orphan*/  X509_PKEY_free (TYPE_1__*) ; 

X509_PKEY *X509_PKEY_new(void)
{
    X509_PKEY *ret = NULL;

    ret = OPENSSL_zalloc(sizeof(*ret));
    if (ret == NULL)
        goto err;

    ret->enc_algor = X509_ALGOR_new();
    ret->enc_pkey = ASN1_OCTET_STRING_new();
    if (ret->enc_algor == NULL || ret->enc_pkey == NULL)
        goto err;

    return ret;
err:
    X509_PKEY_free(ret);
    ASN1err(ASN1_F_X509_PKEY_NEW, ERR_R_MALLOC_FAILURE);
    return NULL;
}