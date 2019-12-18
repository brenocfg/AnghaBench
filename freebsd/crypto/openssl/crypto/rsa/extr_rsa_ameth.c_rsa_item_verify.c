#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_F_RSA_ITEM_VERIFY ; 
 int /*<<< orphan*/  RSA_R_UNSUPPORTED_SIGNATURE_TYPE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rsa_pss_to_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsa_item_verify(EVP_MD_CTX *ctx, const ASN1_ITEM *it, void *asn,
                           X509_ALGOR *sigalg, ASN1_BIT_STRING *sig,
                           EVP_PKEY *pkey)
{
    /* Sanity check: make sure it is PSS */
    if (OBJ_obj2nid(sigalg->algorithm) != EVP_PKEY_RSA_PSS) {
        RSAerr(RSA_F_RSA_ITEM_VERIFY, RSA_R_UNSUPPORTED_SIGNATURE_TYPE);
        return -1;
    }
    if (rsa_pss_to_ctx(ctx, NULL, sigalg, pkey) > 0) {
        /* Carry on */
        return 2;
    }
    return -1;
}