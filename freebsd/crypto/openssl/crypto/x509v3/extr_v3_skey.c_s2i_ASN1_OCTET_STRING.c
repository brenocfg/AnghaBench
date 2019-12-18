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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
typedef  int /*<<< orphan*/  X509V3_CTX ;
struct TYPE_5__ {long length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_hexstr2buf (char const*,long*) ; 
 int /*<<< orphan*/  X509V3_F_S2I_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ASN1_OCTET_STRING *s2i_ASN1_OCTET_STRING(X509V3_EXT_METHOD *method,
                                         X509V3_CTX *ctx, const char *str)
{
    ASN1_OCTET_STRING *oct;
    long length;

    if ((oct = ASN1_OCTET_STRING_new()) == NULL) {
        X509V3err(X509V3_F_S2I_ASN1_OCTET_STRING, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if ((oct->data = OPENSSL_hexstr2buf(str, &length)) == NULL) {
        ASN1_OCTET_STRING_free(oct);
        return NULL;
    }

    oct->length = length;

    return oct;

}