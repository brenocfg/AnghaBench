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
struct TYPE_5__ {int pkey_flags; char const* pem_str; } ;
typedef  TYPE_1__ EVP_PKEY_ASN1_METHOD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int ASN1_PKEY_ALIAS ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* ENGINE_pkey_asn1_find_str (int /*<<< orphan*/ **,char const*,int) ; 
 TYPE_1__* EVP_PKEY_asn1_get0 (int) ; 
 int EVP_PKEY_asn1_get_count () ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

const EVP_PKEY_ASN1_METHOD *EVP_PKEY_asn1_find_str(ENGINE **pe,
                                                   const char *str, int len)
{
    int i;
    const EVP_PKEY_ASN1_METHOD *ameth = NULL;

    if (len == -1)
        len = strlen(str);
    if (pe) {
#ifndef OPENSSL_NO_ENGINE
        ENGINE *e;
        ameth = ENGINE_pkey_asn1_find_str(&e, str, len);
        if (ameth) {
            /*
             * Convert structural into functional reference
             */
            if (!ENGINE_init(e))
                ameth = NULL;
            ENGINE_free(e);
            *pe = e;
            return ameth;
        }
#endif
        *pe = NULL;
    }
    for (i = EVP_PKEY_asn1_get_count(); i-- > 0; ) {
        ameth = EVP_PKEY_asn1_get0(i);
        if (ameth->pkey_flags & ASN1_PKEY_ALIAS)
            continue;
        if ((int)strlen(ameth->pem_str) == len
            && strncasecmp(ameth->pem_str, str, len) == 0)
            return ameth;
    }
    return NULL;
}