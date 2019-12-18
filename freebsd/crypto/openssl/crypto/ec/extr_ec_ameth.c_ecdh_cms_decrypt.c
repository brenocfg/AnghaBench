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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  CMS_RecipientInfo ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * CMS_RecipientInfo_get0_pkey_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_RecipientInfo_kari_get0_orig_id (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_ECDH_CMS_DECRYPT ; 
 int /*<<< orphan*/  EC_R_PEER_KEY_ERROR ; 
 int /*<<< orphan*/  EC_R_SHARED_INFO_ERROR ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_get0_peerkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecdh_cms_set_peerkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecdh_cms_set_shared_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecdh_cms_decrypt(CMS_RecipientInfo *ri)
{
    EVP_PKEY_CTX *pctx;
    pctx = CMS_RecipientInfo_get0_pkey_ctx(ri);
    if (!pctx)
        return 0;
    /* See if we need to set peer key */
    if (!EVP_PKEY_CTX_get0_peerkey(pctx)) {
        X509_ALGOR *alg;
        ASN1_BIT_STRING *pubkey;
        if (!CMS_RecipientInfo_kari_get0_orig_id(ri, &alg, &pubkey,
                                                 NULL, NULL, NULL))
            return 0;
        if (!alg || !pubkey)
            return 0;
        if (!ecdh_cms_set_peerkey(pctx, alg, pubkey)) {
            ECerr(EC_F_ECDH_CMS_DECRYPT, EC_R_PEER_KEY_ERROR);
            return 0;
        }
    }
    /* Set ECDH derivation parameters and initialise unwrap context */
    if (!ecdh_cms_set_shared_info(pctx, ri)) {
        ECerr(EC_F_ECDH_CMS_DECRYPT, EC_R_SHARED_INFO_ERROR);
        return 0;
    }
    return 1;
}