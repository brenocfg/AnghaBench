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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TYPE_MD ; 
 int /*<<< orphan*/ * BIO_find_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_get_md_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_F_CMS_DIGESTALGORITHM_FIND_CTX ; 
 int /*<<< orphan*/  CMS_R_NO_MATCHING_DIGEST ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_MD_CTX_copy_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 int EVP_MD_CTX_type (int /*<<< orphan*/ *) ; 
 int EVP_MD_pkey_type (int /*<<< orphan*/ ) ; 
 int OBJ_obj2nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int cms_DigestAlgorithm_find_ctx(EVP_MD_CTX *mctx, BIO *chain,
                                 X509_ALGOR *mdalg)
{
    int nid;
    const ASN1_OBJECT *mdoid;
    X509_ALGOR_get0(&mdoid, NULL, NULL, mdalg);
    nid = OBJ_obj2nid(mdoid);
    /* Look for digest type to match signature */
    for (;;) {
        EVP_MD_CTX *mtmp;
        chain = BIO_find_type(chain, BIO_TYPE_MD);
        if (chain == NULL) {
            CMSerr(CMS_F_CMS_DIGESTALGORITHM_FIND_CTX,
                   CMS_R_NO_MATCHING_DIGEST);
            return 0;
        }
        BIO_get_md_ctx(chain, &mtmp);
        if (EVP_MD_CTX_type(mtmp) == nid
            /*
             * Workaround for broken implementations that use signature
             * algorithm OID instead of digest.
             */
            || EVP_MD_pkey_type(EVP_MD_CTX_md(mtmp)) == nid)
            return EVP_MD_CTX_copy_ex(mctx, mtmp);
        chain = BIO_next(chain);
    }
}