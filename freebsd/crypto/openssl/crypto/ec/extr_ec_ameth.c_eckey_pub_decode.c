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
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECKEY_PUB_DECODE ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_DECODE_ERROR ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/ *,int*,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0_param (int /*<<< orphan*/ *,unsigned char const**,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * eckey_type2param (int,void const*) ; 
 int /*<<< orphan*/  o2i_ECPublicKey (int /*<<< orphan*/ **,unsigned char const**,int) ; 

__attribute__((used)) static int eckey_pub_decode(EVP_PKEY *pkey, X509_PUBKEY *pubkey)
{
    const unsigned char *p = NULL;
    const void *pval;
    int ptype, pklen;
    EC_KEY *eckey = NULL;
    X509_ALGOR *palg;

    if (!X509_PUBKEY_get0_param(NULL, &p, &pklen, &palg, pubkey))
        return 0;
    X509_ALGOR_get0(NULL, &ptype, &pval, palg);

    eckey = eckey_type2param(ptype, pval);

    if (!eckey) {
        ECerr(EC_F_ECKEY_PUB_DECODE, ERR_R_EC_LIB);
        return 0;
    }

    /* We have parameters now set public key */
    if (!o2i_ECPublicKey(&eckey, &p, pklen)) {
        ECerr(EC_F_ECKEY_PUB_DECODE, EC_R_DECODE_ERROR);
        goto ecerr;
    }

    EVP_PKEY_assign_EC_KEY(pkey, eckey);
    return 1;

 ecerr:
    EC_KEY_free(eckey);
    return 0;
}