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
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/ * OSSL_STORE_INFO_new_CRL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_STRING_X509_CRL ; 
 int /*<<< orphan*/  X509_CRL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509_CRL (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OSSL_STORE_INFO *try_decode_X509CRL(const char *pem_name,
                                           const char *pem_header,
                                           const unsigned char *blob,
                                           size_t len, void **pctx,
                                           int *matchcount,
                                           const UI_METHOD *ui_method,
                                           void *ui_data)
{
    OSSL_STORE_INFO *store_info = NULL;
    X509_CRL *crl = NULL;

    if (pem_name != NULL) {
        if (strcmp(pem_name, PEM_STRING_X509_CRL) != 0)
            /* No match */
            return NULL;
        *matchcount = 1;
    }

    if ((crl = d2i_X509_CRL(NULL, &blob, len)) != NULL) {
        *matchcount = 1;
        store_info = OSSL_STORE_INFO_new_CRL(crl);
    }

    if (store_info == NULL)
        X509_CRL_free(crl);

    return store_info;
}