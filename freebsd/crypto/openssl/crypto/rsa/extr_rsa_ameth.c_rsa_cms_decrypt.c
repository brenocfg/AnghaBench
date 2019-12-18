#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* parameter; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_4__ X509_ALGOR ;
struct TYPE_14__ {TYPE_4__* pSourceFunc; int /*<<< orphan*/  hashFunc; int /*<<< orphan*/  maskHash; } ;
struct TYPE_11__ {TYPE_1__* octet_string; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ value; } ;
struct TYPE_10__ {unsigned char* data; int length; } ;
typedef  TYPE_5__ RSA_OAEP_PARAMS ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  CMS_RecipientInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * CMS_RecipientInfo_get0_pkey_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_RecipientInfo_ktri_get0_algs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__**) ; 
 scalar_t__ EVP_PKEY_CTX_set0_rsa_oaep_label (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_mgf1_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_oaep_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NID_pSpecified ; 
 int NID_rsaEncryption ; 
 int NID_rsaesOaep ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_F_RSA_CMS_DECRYPT ; 
 int /*<<< orphan*/  RSA_OAEP_PARAMS_free (TYPE_5__*) ; 
 int /*<<< orphan*/  RSA_PKCS1_OAEP_PADDING ; 
 int /*<<< orphan*/  RSA_R_INVALID_LABEL ; 
 int /*<<< orphan*/  RSA_R_INVALID_OAEP_PARAMETERS ; 
 int /*<<< orphan*/  RSA_R_UNSUPPORTED_ENCRYPTION_TYPE ; 
 int /*<<< orphan*/  RSA_R_UNSUPPORTED_LABEL_SOURCE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/ * rsa_algor_to_md (int /*<<< orphan*/ ) ; 
 TYPE_5__* rsa_oaep_decode (TYPE_4__*) ; 

__attribute__((used)) static int rsa_cms_decrypt(CMS_RecipientInfo *ri)
{
    EVP_PKEY_CTX *pkctx;
    X509_ALGOR *cmsalg;
    int nid;
    int rv = -1;
    unsigned char *label = NULL;
    int labellen = 0;
    const EVP_MD *mgf1md = NULL, *md = NULL;
    RSA_OAEP_PARAMS *oaep;

    pkctx = CMS_RecipientInfo_get0_pkey_ctx(ri);
    if (pkctx == NULL)
        return 0;
    if (!CMS_RecipientInfo_ktri_get0_algs(ri, NULL, NULL, &cmsalg))
        return -1;
    nid = OBJ_obj2nid(cmsalg->algorithm);
    if (nid == NID_rsaEncryption)
        return 1;
    if (nid != NID_rsaesOaep) {
        RSAerr(RSA_F_RSA_CMS_DECRYPT, RSA_R_UNSUPPORTED_ENCRYPTION_TYPE);
        return -1;
    }
    /* Decode OAEP parameters */
    oaep = rsa_oaep_decode(cmsalg);

    if (oaep == NULL) {
        RSAerr(RSA_F_RSA_CMS_DECRYPT, RSA_R_INVALID_OAEP_PARAMETERS);
        goto err;
    }

    mgf1md = rsa_algor_to_md(oaep->maskHash);
    if (mgf1md == NULL)
        goto err;
    md = rsa_algor_to_md(oaep->hashFunc);
    if (md == NULL)
        goto err;

    if (oaep->pSourceFunc != NULL) {
        X509_ALGOR *plab = oaep->pSourceFunc;

        if (OBJ_obj2nid(plab->algorithm) != NID_pSpecified) {
            RSAerr(RSA_F_RSA_CMS_DECRYPT, RSA_R_UNSUPPORTED_LABEL_SOURCE);
            goto err;
        }
        if (plab->parameter->type != V_ASN1_OCTET_STRING) {
            RSAerr(RSA_F_RSA_CMS_DECRYPT, RSA_R_INVALID_LABEL);
            goto err;
        }

        label = plab->parameter->value.octet_string->data;
        /* Stop label being freed when OAEP parameters are freed */
        plab->parameter->value.octet_string->data = NULL;
        labellen = plab->parameter->value.octet_string->length;
    }

    if (EVP_PKEY_CTX_set_rsa_padding(pkctx, RSA_PKCS1_OAEP_PADDING) <= 0)
        goto err;
    if (EVP_PKEY_CTX_set_rsa_oaep_md(pkctx, md) <= 0)
        goto err;
    if (EVP_PKEY_CTX_set_rsa_mgf1_md(pkctx, mgf1md) <= 0)
        goto err;
    if (EVP_PKEY_CTX_set0_rsa_oaep_label(pkctx, label, labellen) <= 0)
        goto err;
    /* Carry on */
    rv = 1;

 err:
    RSA_OAEP_PARAMS_free(oaep);
    return rv;
}