#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_8__ {int /*<<< orphan*/  ec; } ;
struct TYPE_9__ {TYPE_1__ pkey; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EC_KEY_new () ; 
 int /*<<< orphan*/  EC_KEY_set_group (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_2__* EVP_PKEY_CTX_get0_pkey (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_derive_set_peer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_2__*) ; 
 TYPE_2__* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_EC_KEY (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ NID_X9_62_id_ecPublicKey ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/  const*) ; 
 int V_ASN1_NULL ; 
 int V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/  const**,int*,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * eckey_type2param (int,void const*) ; 
 int /*<<< orphan*/  o2i_ECPublicKey (int /*<<< orphan*/ **,unsigned char const**,int) ; 

__attribute__((used)) static int ecdh_cms_set_peerkey(EVP_PKEY_CTX *pctx,
                                X509_ALGOR *alg, ASN1_BIT_STRING *pubkey)
{
    const ASN1_OBJECT *aoid;
    int atype;
    const void *aval;
    int rv = 0;
    EVP_PKEY *pkpeer = NULL;
    EC_KEY *ecpeer = NULL;
    const unsigned char *p;
    int plen;
    X509_ALGOR_get0(&aoid, &atype, &aval, alg);
    if (OBJ_obj2nid(aoid) != NID_X9_62_id_ecPublicKey)
        goto err;
    /* If absent parameters get group from main key */
    if (atype == V_ASN1_UNDEF || atype == V_ASN1_NULL) {
        const EC_GROUP *grp;
        EVP_PKEY *pk;
        pk = EVP_PKEY_CTX_get0_pkey(pctx);
        if (!pk)
            goto err;
        grp = EC_KEY_get0_group(pk->pkey.ec);
        ecpeer = EC_KEY_new();
        if (ecpeer == NULL)
            goto err;
        if (!EC_KEY_set_group(ecpeer, grp))
            goto err;
    } else {
        ecpeer = eckey_type2param(atype, aval);
        if (!ecpeer)
            goto err;
    }
    /* We have parameters now set public key */
    plen = ASN1_STRING_length(pubkey);
    p = ASN1_STRING_get0_data(pubkey);
    if (!p || !plen)
        goto err;
    if (!o2i_ECPublicKey(&ecpeer, &p, plen))
        goto err;
    pkpeer = EVP_PKEY_new();
    if (pkpeer == NULL)
        goto err;
    EVP_PKEY_set1_EC_KEY(pkpeer, ecpeer);
    if (EVP_PKEY_derive_set_peer(pctx, pkpeer) > 0)
        rv = 1;
 err:
    EC_KEY_free(ecpeer);
    EVP_PKEY_free(pkpeer);
    return rv;
}