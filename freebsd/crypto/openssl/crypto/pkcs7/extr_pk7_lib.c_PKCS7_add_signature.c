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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  PKCS7_SIGNER_INFO ;
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_get_default_digest_nid (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_ADD_SIGNATURE ; 
 int /*<<< orphan*/  PKCS7_R_NO_DEFAULT_DIGEST ; 
 int /*<<< orphan*/  PKCS7_SIGNER_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS7_SIGNER_INFO_new () ; 
 int /*<<< orphan*/  PKCS7_SIGNER_INFO_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PKCS7_add_signer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PKCS7_SIGNER_INFO *PKCS7_add_signature(PKCS7 *p7, X509 *x509, EVP_PKEY *pkey,
                                       const EVP_MD *dgst)
{
    PKCS7_SIGNER_INFO *si = NULL;

    if (dgst == NULL) {
        int def_nid;
        if (EVP_PKEY_get_default_digest_nid(pkey, &def_nid) <= 0)
            goto err;
        dgst = EVP_get_digestbynid(def_nid);
        if (dgst == NULL) {
            PKCS7err(PKCS7_F_PKCS7_ADD_SIGNATURE, PKCS7_R_NO_DEFAULT_DIGEST);
            goto err;
        }
    }

    if ((si = PKCS7_SIGNER_INFO_new()) == NULL)
        goto err;
    if (!PKCS7_SIGNER_INFO_set(si, x509, pkey, dgst))
        goto err;
    if (!PKCS7_add_signer(p7, si))
        goto err;
    return si;
 err:
    PKCS7_SIGNER_INFO_free(si);
    return NULL;
}