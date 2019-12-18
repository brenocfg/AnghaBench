#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_1__* meth; } ;
struct TYPE_18__ {int /*<<< orphan*/  enc_flag; TYPE_9__* group; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/  version; } ;
struct TYPE_17__ {int /*<<< orphan*/ * publicKey; int /*<<< orphan*/ * privateKey; int /*<<< orphan*/  version; scalar_t__ parameters; } ;
struct TYPE_16__ {scalar_t__ (* keygenpub ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ EC_PRIVATEKEY ;
typedef  TYPE_3__ EC_KEY ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_D2I_ECPRIVATEKEY ; 
 int /*<<< orphan*/  EC_GROUP_free (TYPE_9__*) ; 
 TYPE_9__* EC_GROUP_new_from_ecpkparameters (scalar_t__) ; 
 int /*<<< orphan*/  EC_KEY_free (TYPE_3__*) ; 
 TYPE_3__* EC_KEY_new () ; 
 int /*<<< orphan*/  EC_KEY_oct2key (TYPE_3__*,unsigned char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_KEY_oct2priv (TYPE_3__*,unsigned char*,int) ; 
 int /*<<< orphan*/  EC_PKEY_NO_PUBKEY ; 
 int /*<<< orphan*/  EC_POINT_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_9__*) ; 
 int /*<<< orphan*/  EC_PRIVATEKEY_free (TYPE_2__*) ; 
 int /*<<< orphan*/  EC_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_2__* d2i_EC_PRIVATEKEY (int /*<<< orphan*/ *,unsigned char const**,long) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 

EC_KEY *d2i_ECPrivateKey(EC_KEY **a, const unsigned char **in, long len)
{
    EC_KEY *ret = NULL;
    EC_PRIVATEKEY *priv_key = NULL;
    const unsigned char *p = *in;

    if ((priv_key = d2i_EC_PRIVATEKEY(NULL, &p, len)) == NULL) {
        ECerr(EC_F_D2I_ECPRIVATEKEY, ERR_R_EC_LIB);
        return NULL;
    }

    if (a == NULL || *a == NULL) {
        if ((ret = EC_KEY_new()) == NULL) {
            ECerr(EC_F_D2I_ECPRIVATEKEY, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    } else
        ret = *a;

    if (priv_key->parameters) {
        EC_GROUP_free(ret->group);
        ret->group = EC_GROUP_new_from_ecpkparameters(priv_key->parameters);
    }

    if (ret->group == NULL) {
        ECerr(EC_F_D2I_ECPRIVATEKEY, ERR_R_EC_LIB);
        goto err;
    }

    ret->version = priv_key->version;

    if (priv_key->privateKey) {
        ASN1_OCTET_STRING *pkey = priv_key->privateKey;
        if (EC_KEY_oct2priv(ret, ASN1_STRING_get0_data(pkey),
                            ASN1_STRING_length(pkey)) == 0)
            goto err;
    } else {
        ECerr(EC_F_D2I_ECPRIVATEKEY, EC_R_MISSING_PRIVATE_KEY);
        goto err;
    }

    EC_POINT_clear_free(ret->pub_key);
    ret->pub_key = EC_POINT_new(ret->group);
    if (ret->pub_key == NULL) {
        ECerr(EC_F_D2I_ECPRIVATEKEY, ERR_R_EC_LIB);
        goto err;
    }

    if (priv_key->publicKey) {
        const unsigned char *pub_oct;
        int pub_oct_len;

        pub_oct = ASN1_STRING_get0_data(priv_key->publicKey);
        pub_oct_len = ASN1_STRING_length(priv_key->publicKey);
        if (!EC_KEY_oct2key(ret, pub_oct, pub_oct_len, NULL)) {
            ECerr(EC_F_D2I_ECPRIVATEKEY, ERR_R_EC_LIB);
            goto err;
        }
    } else {
        if (ret->group->meth->keygenpub == NULL
            || ret->group->meth->keygenpub(ret) == 0)
                goto err;
        /* Remember the original private-key-only encoding. */
        ret->enc_flag |= EC_PKEY_NO_PUBKEY;
    }

    if (a)
        *a = ret;
    EC_PRIVATEKEY_free(priv_key);
    *in = p;
    return ret;

 err:
    if (a == NULL || *a != ret)
        EC_KEY_free(ret);
    EC_PRIVATEKEY_free(priv_key);
    return NULL;
}