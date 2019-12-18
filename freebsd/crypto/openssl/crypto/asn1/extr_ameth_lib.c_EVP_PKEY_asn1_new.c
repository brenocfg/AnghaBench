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
struct TYPE_5__ {int pkey_id; int pkey_base_id; int pkey_flags; void* pem_str; void* info; } ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;

/* Variables and functions */
 int ASN1_PKEY_DYNAMIC ; 
 int /*<<< orphan*/  EVP_PKEY_asn1_free (TYPE_1__*) ; 
 void* OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

EVP_PKEY_ASN1_METHOD *EVP_PKEY_asn1_new(int id, int flags,
                                        const char *pem_str, const char *info)
{
    EVP_PKEY_ASN1_METHOD *ameth = OPENSSL_zalloc(sizeof(*ameth));

    if (ameth == NULL)
        return NULL;

    ameth->pkey_id = id;
    ameth->pkey_base_id = id;
    ameth->pkey_flags = flags | ASN1_PKEY_DYNAMIC;

    if (info) {
        ameth->info = OPENSSL_strdup(info);
        if (!ameth->info)
            goto err;
    }

    if (pem_str) {
        ameth->pem_str = OPENSSL_strdup(pem_str);
        if (!ameth->pem_str)
            goto err;
    }

    return ameth;

 err:
    EVP_PKEY_asn1_free(ameth);
    return NULL;

}