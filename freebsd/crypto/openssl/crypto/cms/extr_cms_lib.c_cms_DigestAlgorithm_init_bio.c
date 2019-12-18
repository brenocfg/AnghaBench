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
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_f_md () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CMS_F_CMS_DIGESTALGORITHM_INIT_BIO ; 
 int /*<<< orphan*/  CMS_R_MD_BIO_INIT_ERROR ; 
 int /*<<< orphan*/  CMS_R_UNKNOWN_DIGEST_ALGORITHM ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BIO *cms_DigestAlgorithm_init_bio(X509_ALGOR *digestAlgorithm)
{
    BIO *mdbio = NULL;
    const ASN1_OBJECT *digestoid;
    const EVP_MD *digest;
    X509_ALGOR_get0(&digestoid, NULL, NULL, digestAlgorithm);
    digest = EVP_get_digestbyobj(digestoid);
    if (!digest) {
        CMSerr(CMS_F_CMS_DIGESTALGORITHM_INIT_BIO,
               CMS_R_UNKNOWN_DIGEST_ALGORITHM);
        goto err;
    }
    mdbio = BIO_new(BIO_f_md());
    if (mdbio == NULL || !BIO_set_md(mdbio, digest)) {
        CMSerr(CMS_F_CMS_DIGESTALGORITHM_INIT_BIO, CMS_R_MD_BIO_INIT_ERROR);
        goto err;
    }
    return mdbio;
 err:
    BIO_free(mdbio);
    return NULL;
}