#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  point_conversion_form_t ;
struct TYPE_39__ {scalar_t__ k3; scalar_t__ k2; scalar_t__ k1; } ;
typedef  TYPE_9__ X9_62_PENTANOMIAL ;
struct TYPE_38__ {TYPE_9__* ppBasis; int /*<<< orphan*/  tpBasis; } ;
struct TYPE_28__ {long m; TYPE_8__ p; int /*<<< orphan*/  type; } ;
typedef  TYPE_10__ X9_62_CHARACTERISTIC_TWO ;
struct TYPE_36__ {int /*<<< orphan*/ * prime; TYPE_10__* char_two; int /*<<< orphan*/  ptr; } ;
struct TYPE_37__ {TYPE_6__ p; int /*<<< orphan*/  fieldType; } ;
struct TYPE_35__ {TYPE_1__* seed; TYPE_4__* b; TYPE_3__* a; } ;
struct TYPE_34__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_33__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_32__ {int* data; int /*<<< orphan*/  length; } ;
struct TYPE_31__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_30__ {int /*<<< orphan*/ * cofactor; int /*<<< orphan*/ * order; TYPE_2__* base; TYPE_5__* curve; TYPE_7__* fieldID; } ;
struct TYPE_29__ {int /*<<< orphan*/  seed_len; int /*<<< orphan*/ * seed; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_11__ EC_GROUP ;
typedef  TYPE_12__ ECPARAMETERS ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 long ASN1_INTEGER_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS ; 
 TYPE_11__* EC_GROUP_dup (TYPE_11__*) ; 
 int /*<<< orphan*/  EC_GROUP_free (TYPE_11__*) ; 
 TYPE_11__* EC_GROUP_new_by_curve_name (int) ; 
 TYPE_11__* EC_GROUP_new_curve_GF2m (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_11__* EC_GROUP_new_curve_GFp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_asn1_flag (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_GROUP_set_generator (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_point_conversion_form (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int EC_GROUP_set_seed (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_11__*) ; 
 int /*<<< orphan*/  EC_POINT_oct2point (TYPE_11__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_ASN1_ERROR ; 
 int /*<<< orphan*/  EC_R_FIELD_TOO_LARGE ; 
 int /*<<< orphan*/  EC_R_GF2M_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EC_R_INVALID_FIELD ; 
 int /*<<< orphan*/  EC_R_INVALID_GROUP_ORDER ; 
 int /*<<< orphan*/  EC_R_INVALID_PENTANOMIAL_BASIS ; 
 int /*<<< orphan*/  EC_R_INVALID_TRINOMIAL_BASIS ; 
 int /*<<< orphan*/  EC_R_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int NID_X9_62_characteristic_two_field ; 
 int NID_X9_62_onBasis ; 
 int NID_X9_62_ppBasis ; 
 int NID_X9_62_prime_field ; 
 int NID_X9_62_tpBasis ; 
 int NID_secp224r1 ; 
 int NID_undef ; 
 int NID_wap_wsg_idm_ecid_wtls12 ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 long OPENSSL_ECC_MAX_FIELD_BITS ; 
 int /*<<< orphan*/  OPENSSL_EC_EXPLICIT_CURVE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 int ec_curve_nid_from_params (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

EC_GROUP *EC_GROUP_new_from_ecparameters(const ECPARAMETERS *params)
{
    int ok = 0, tmp;
    EC_GROUP *ret = NULL, *dup = NULL;
    BIGNUM *p = NULL, *a = NULL, *b = NULL;
    EC_POINT *point = NULL;
    long field_bits;
    int curve_name = NID_undef;
    BN_CTX *ctx = NULL;

    if (!params->fieldID || !params->fieldID->fieldType ||
        !params->fieldID->p.ptr) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_ASN1_ERROR);
        goto err;
    }

    /*
     * Now extract the curve parameters a and b. Note that, although SEC 1
     * specifies the length of their encodings, historical versions of OpenSSL
     * encoded them incorrectly, so we must accept any length for backwards
     * compatibility.
     */
    if (!params->curve || !params->curve->a ||
        !params->curve->a->data || !params->curve->b ||
        !params->curve->b->data) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_ASN1_ERROR);
        goto err;
    }
    a = BN_bin2bn(params->curve->a->data, params->curve->a->length, NULL);
    if (a == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_BN_LIB);
        goto err;
    }
    b = BN_bin2bn(params->curve->b->data, params->curve->b->length, NULL);
    if (b == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_BN_LIB);
        goto err;
    }

    /* get the field parameters */
    tmp = OBJ_obj2nid(params->fieldID->fieldType);
    if (tmp == NID_X9_62_characteristic_two_field)
#ifdef OPENSSL_NO_EC2M
    {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_GF2M_NOT_SUPPORTED);
        goto err;
    }
#else
    {
        X9_62_CHARACTERISTIC_TWO *char_two;

        char_two = params->fieldID->p.char_two;

        field_bits = char_two->m;
        if (field_bits > OPENSSL_ECC_MAX_FIELD_BITS) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_FIELD_TOO_LARGE);
            goto err;
        }

        if ((p = BN_new()) == NULL) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_MALLOC_FAILURE);
            goto err;
        }

        /* get the base type */
        tmp = OBJ_obj2nid(char_two->type);

        if (tmp == NID_X9_62_tpBasis) {
            long tmp_long;

            if (!char_two->p.tpBasis) {
                ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_ASN1_ERROR);
                goto err;
            }

            tmp_long = ASN1_INTEGER_get(char_two->p.tpBasis);

            if (!(char_two->m > tmp_long && tmp_long > 0)) {
                ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS,
                      EC_R_INVALID_TRINOMIAL_BASIS);
                goto err;
            }

            /* create the polynomial */
            if (!BN_set_bit(p, (int)char_two->m))
                goto err;
            if (!BN_set_bit(p, (int)tmp_long))
                goto err;
            if (!BN_set_bit(p, 0))
                goto err;
        } else if (tmp == NID_X9_62_ppBasis) {
            X9_62_PENTANOMIAL *penta;

            penta = char_two->p.ppBasis;
            if (!penta) {
                ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_ASN1_ERROR);
                goto err;
            }

            if (!
                (char_two->m > penta->k3 && penta->k3 > penta->k2
                 && penta->k2 > penta->k1 && penta->k1 > 0)) {
                ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS,
                      EC_R_INVALID_PENTANOMIAL_BASIS);
                goto err;
            }

            /* create the polynomial */
            if (!BN_set_bit(p, (int)char_two->m))
                goto err;
            if (!BN_set_bit(p, (int)penta->k1))
                goto err;
            if (!BN_set_bit(p, (int)penta->k2))
                goto err;
            if (!BN_set_bit(p, (int)penta->k3))
                goto err;
            if (!BN_set_bit(p, 0))
                goto err;
        } else if (tmp == NID_X9_62_onBasis) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_NOT_IMPLEMENTED);
            goto err;
        } else {                /* error */

            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_ASN1_ERROR);
            goto err;
        }

        /* create the EC_GROUP structure */
        ret = EC_GROUP_new_curve_GF2m(p, a, b, NULL);
    }
#endif
    else if (tmp == NID_X9_62_prime_field) {
        /* we have a curve over a prime field */
        /* extract the prime number */
        if (!params->fieldID->p.prime) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_ASN1_ERROR);
            goto err;
        }
        p = ASN1_INTEGER_to_BN(params->fieldID->p.prime, NULL);
        if (p == NULL) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_ASN1_LIB);
            goto err;
        }

        if (BN_is_negative(p) || BN_is_zero(p)) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_INVALID_FIELD);
            goto err;
        }

        field_bits = BN_num_bits(p);
        if (field_bits > OPENSSL_ECC_MAX_FIELD_BITS) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_FIELD_TOO_LARGE);
            goto err;
        }

        /* create the EC_GROUP structure */
        ret = EC_GROUP_new_curve_GFp(p, a, b, NULL);
    } else {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_INVALID_FIELD);
        goto err;
    }

    if (ret == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }

    /* extract seed (optional) */
    if (params->curve->seed != NULL) {
        OPENSSL_free(ret->seed);
        if ((ret->seed = OPENSSL_malloc(params->curve->seed->length)) == NULL) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        memcpy(ret->seed, params->curve->seed->data,
               params->curve->seed->length);
        ret->seed_len = params->curve->seed->length;
    }

    if (!params->order || !params->base || !params->base->data) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_ASN1_ERROR);
        goto err;
    }

    if ((point = EC_POINT_new(ret)) == NULL)
        goto err;

    /* set the point conversion form */
    EC_GROUP_set_point_conversion_form(ret, (point_conversion_form_t)
                                       (params->base->data[0] & ~0x01));

    /* extract the ec point */
    if (!EC_POINT_oct2point(ret, point, params->base->data,
                            params->base->length, NULL)) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }

    /* extract the order */
    if ((a = ASN1_INTEGER_to_BN(params->order, a)) == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_ASN1_LIB);
        goto err;
    }
    if (BN_is_negative(a) || BN_is_zero(a)) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_INVALID_GROUP_ORDER);
        goto err;
    }
    if (BN_num_bits(a) > (int)field_bits + 1) { /* Hasse bound */
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, EC_R_INVALID_GROUP_ORDER);
        goto err;
    }

    /* extract the cofactor (optional) */
    if (params->cofactor == NULL) {
        BN_free(b);
        b = NULL;
    } else if ((b = ASN1_INTEGER_to_BN(params->cofactor, b)) == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_ASN1_LIB);
        goto err;
    }
    /* set the generator, order and cofactor (if present) */
    if (!EC_GROUP_set_generator(ret, point, a, b)) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }

    /*
     * Check if the explicit parameters group just created matches one of the
     * built-in curves.
     *
     * We create a copy of the group just built, so that we can remove optional
     * fields for the lookup: we do this to avoid the possibility that one of
     * the optional parameters is used to force the library into using a less
     * performant and less secure EC_METHOD instead of the specialized one.
     * In any case, `seed` is not really used in any computation, while a
     * cofactor different from the one in the built-in table is just
     * mathematically wrong anyway and should not be used.
     */
    if ((ctx = BN_CTX_new()) == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_BN_LIB);
        goto err;
    }
    if ((dup = EC_GROUP_dup(ret)) == NULL
            || EC_GROUP_set_seed(dup, NULL, 0) != 1
            || !EC_GROUP_set_generator(dup, point, a, NULL)) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_EC_LIB);
        goto err;
    }
    if ((curve_name = ec_curve_nid_from_params(dup, ctx)) != NID_undef) {
        /*
         * The input explicit parameters successfully matched one of the
         * built-in curves: often for built-in curves we have specialized
         * methods with better performance and hardening.
         *
         * In this case we replace the `EC_GROUP` created through explicit
         * parameters with one created from a named group.
         */
        EC_GROUP *named_group = NULL;

#ifndef OPENSSL_NO_EC_NISTP_64_GCC_128
        /*
         * NID_wap_wsg_idm_ecid_wtls12 and NID_secp224r1 are both aliases for
         * the same curve, we prefer the SECP nid when matching explicit
         * parameters as that is associated with a specialized EC_METHOD.
         */
        if (curve_name == NID_wap_wsg_idm_ecid_wtls12)
            curve_name = NID_secp224r1;
#endif /* !def(OPENSSL_NO_EC_NISTP_64_GCC_128) */

        if ((named_group = EC_GROUP_new_by_curve_name(curve_name)) == NULL) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_ECPARAMETERS, ERR_R_EC_LIB);
            goto err;
        }
        EC_GROUP_free(ret);
        ret = named_group;

        /*
         * Set the flag so that EC_GROUPs created from explicit parameters are
         * serialized using explicit parameters by default.
         */
        EC_GROUP_set_asn1_flag(ret, OPENSSL_EC_EXPLICIT_CURVE);
    }

    ok = 1;

 err:
    if (!ok) {
        EC_GROUP_free(ret);
        ret = NULL;
    }
    EC_GROUP_free(dup);

    BN_free(p);
    BN_free(a);
    BN_free(b);
    EC_POINT_free(point);

    BN_CTX_free(ctx);

    return ret;
}