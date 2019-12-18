#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rsa; } ;
struct TYPE_8__ {TYPE_1__* ameth; TYPE_2__ pkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS8_pkey_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  RSA_F_RSA_PRIV_ENCODE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2d_RSAPrivateKey (int /*<<< orphan*/ ,unsigned char**) ; 
 int /*<<< orphan*/  rsa_param_encode (TYPE_3__ const*,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static int rsa_priv_encode(PKCS8_PRIV_KEY_INFO *p8, const EVP_PKEY *pkey)
{
    unsigned char *rk = NULL;
    int rklen;
    ASN1_STRING *str;
    int strtype;

    if (!rsa_param_encode(pkey, &str, &strtype))
        return 0;
    rklen = i2d_RSAPrivateKey(pkey->pkey.rsa, &rk);

    if (rklen <= 0) {
        RSAerr(RSA_F_RSA_PRIV_ENCODE, ERR_R_MALLOC_FAILURE);
        ASN1_STRING_free(str);
        return 0;
    }

    if (!PKCS8_pkey_set0(p8, OBJ_nid2obj(pkey->ameth->pkey_id), 0,
                         strtype, str, rk, rklen)) {
        RSAerr(RSA_F_RSA_PRIV_ENCODE, ERR_R_MALLOC_FAILURE);
        ASN1_STRING_free(str);
        return 0;
    }

    return 1;
}