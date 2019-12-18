#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_2__ X509_ALGOR ;
struct TYPE_15__ {scalar_t__ type; int flags; scalar_t__ length; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {TYPE_1__* ameth; } ;
struct TYPE_12__ {int (* item_verify ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,TYPE_2__*,TYPE_4__*,TYPE_3__*) ;scalar_t__ pkey_id; } ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  TYPE_4__ ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_ITEM_VERIFY ; 
 int /*<<< orphan*/  ASN1_R_INVALID_BIT_STRING_BITS_LEFT ; 
 int /*<<< orphan*/  ASN1_R_UNKNOWN_MESSAGE_DIGEST_ALGORITHM ; 
 int /*<<< orphan*/  ASN1_R_UNKNOWN_SIGNATURE_ALGORITHM ; 
 int /*<<< orphan*/  ASN1_R_WRONG_PUBLIC_KEY_TYPE ; 
 int ASN1_item_i2d (void*,unsigned char**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int EVP_DigestVerify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 scalar_t__ EVP_PKEY_type (int) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_find_sigid_algs (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 scalar_t__ V_ASN1_BIT_STRING ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,TYPE_2__*,TYPE_4__*,TYPE_3__*) ; 

int ASN1_item_verify(const ASN1_ITEM *it, X509_ALGOR *a,
                     ASN1_BIT_STRING *signature, void *asn, EVP_PKEY *pkey)
{
    EVP_MD_CTX *ctx = NULL;
    unsigned char *buf_in = NULL;
    int ret = -1, inl = 0;
    int mdnid, pknid;
    size_t inll = 0;

    if (!pkey) {
        ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ERR_R_PASSED_NULL_PARAMETER);
        return -1;
    }

    if (signature->type == V_ASN1_BIT_STRING && signature->flags & 0x7) {
        ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ASN1_R_INVALID_BIT_STRING_BITS_LEFT);
        return -1;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* Convert signature OID into digest and public key OIDs */
    if (!OBJ_find_sigid_algs(OBJ_obj2nid(a->algorithm), &mdnid, &pknid)) {
        ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ASN1_R_UNKNOWN_SIGNATURE_ALGORITHM);
        goto err;
    }
    if (mdnid == NID_undef) {
        if (!pkey->ameth || !pkey->ameth->item_verify) {
            ASN1err(ASN1_F_ASN1_ITEM_VERIFY,
                    ASN1_R_UNKNOWN_SIGNATURE_ALGORITHM);
            goto err;
        }
        ret = pkey->ameth->item_verify(ctx, it, asn, a, signature, pkey);
        /*
         * Return value of 2 means carry on, anything else means we exit
         * straight away: either a fatal error of the underlying verification
         * routine handles all verification.
         */
        if (ret != 2)
            goto err;
        ret = -1;
    } else {
        const EVP_MD *type = EVP_get_digestbynid(mdnid);

        if (type == NULL) {
            ASN1err(ASN1_F_ASN1_ITEM_VERIFY,
                    ASN1_R_UNKNOWN_MESSAGE_DIGEST_ALGORITHM);
            goto err;
        }

        /* Check public key OID matches public key type */
        if (EVP_PKEY_type(pknid) != pkey->ameth->pkey_id) {
            ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ASN1_R_WRONG_PUBLIC_KEY_TYPE);
            goto err;
        }

        if (!EVP_DigestVerifyInit(ctx, NULL, type, NULL, pkey)) {
            ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ERR_R_EVP_LIB);
            ret = 0;
            goto err;
        }

    }

    inl = ASN1_item_i2d(asn, &buf_in, it);
    if (inl <= 0) {
        ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    if (buf_in == NULL) {
        ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    inll = inl;

    ret = EVP_DigestVerify(ctx, signature->data, (size_t)signature->length,
                           buf_in, inl);
    if (ret <= 0) {
        ASN1err(ASN1_F_ASN1_ITEM_VERIFY, ERR_R_EVP_LIB);
        goto err;
    }
    ret = 1;
 err:
    OPENSSL_clear_free(buf_in, inll);
    EVP_MD_CTX_free(ctx);
    return ret;
}