#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_RSA_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_F_RSA_PUB_DECODE ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0_param (int /*<<< orphan*/ *,unsigned char const**,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_RSAPublicKey (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int /*<<< orphan*/  rsa_param_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsa_pub_decode(EVP_PKEY *pkey, X509_PUBKEY *pubkey)
{
    const unsigned char *p;
    int pklen;
    X509_ALGOR *alg;
    RSA *rsa = NULL;

    if (!X509_PUBKEY_get0_param(NULL, &p, &pklen, &alg, pubkey))
        return 0;
    if ((rsa = d2i_RSAPublicKey(NULL, &p, pklen)) == NULL) {
        RSAerr(RSA_F_RSA_PUB_DECODE, ERR_R_RSA_LIB);
        return 0;
    }
    if (!rsa_param_decode(rsa, alg)) {
        RSA_free(rsa);
        return 0;
    }
    if (!EVP_PKEY_assign(pkey, pkey->ameth->pkey_id, rsa)) {
        RSA_free(rsa);
        return 0;
    }
    return 1;
}