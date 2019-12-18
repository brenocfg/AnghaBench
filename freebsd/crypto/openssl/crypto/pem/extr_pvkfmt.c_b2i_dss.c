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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int /*<<< orphan*/  DSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_DSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_F_B2I_DSS ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lebn (unsigned char const**,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static EVP_PKEY *b2i_dss(const unsigned char **in,
                         unsigned int bitlen, int ispub)
{
    const unsigned char *p = *in;
    EVP_PKEY *ret = NULL;
    DSA *dsa = NULL;
    BN_CTX *ctx = NULL;
    unsigned int nbyte;
    BIGNUM *pbn = NULL, *qbn = NULL, *gbn = NULL, *priv_key = NULL;
    BIGNUM *pub_key = NULL;

    nbyte = (bitlen + 7) >> 3;

    dsa = DSA_new();
    ret = EVP_PKEY_new();
    if (dsa == NULL || ret == NULL)
        goto memerr;
    if (!read_lebn(&p, nbyte, &pbn))
        goto memerr;

    if (!read_lebn(&p, 20, &qbn))
        goto memerr;

    if (!read_lebn(&p, nbyte, &gbn))
        goto memerr;

    if (ispub) {
        if (!read_lebn(&p, nbyte, &pub_key))
            goto memerr;
    } else {
        if (!read_lebn(&p, 20, &priv_key))
            goto memerr;

        /* Set constant time flag before public key calculation */
        BN_set_flags(priv_key, BN_FLG_CONSTTIME);

        /* Calculate public key */
        pub_key = BN_new();
        if (pub_key == NULL)
            goto memerr;
        if ((ctx = BN_CTX_new()) == NULL)
            goto memerr;

        if (!BN_mod_exp(pub_key, gbn, priv_key, pbn, ctx))
            goto memerr;

        BN_CTX_free(ctx);
        ctx = NULL;
    }
    if (!DSA_set0_pqg(dsa, pbn, qbn, gbn))
        goto memerr;
    pbn = qbn = gbn = NULL;
    if (!DSA_set0_key(dsa, pub_key, priv_key))
        goto memerr;
    pub_key = priv_key = NULL;

    if (!EVP_PKEY_set1_DSA(ret, dsa))
        goto memerr;
    DSA_free(dsa);
    *in = p;
    return ret;

 memerr:
    PEMerr(PEM_F_B2I_DSS, ERR_R_MALLOC_FAILURE);
    DSA_free(dsa);
    BN_free(pbn);
    BN_free(qbn);
    BN_free(gbn);
    BN_free(pub_key);
    BN_free(priv_key);
    EVP_PKEY_free(ret);
    BN_CTX_free(ctx);
    return NULL;
}