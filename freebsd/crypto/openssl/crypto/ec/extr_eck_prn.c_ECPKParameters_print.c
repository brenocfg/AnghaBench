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
typedef  scalar_t__ point_conversion_form_t ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_bn_print (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_new () ; 
 int /*<<< orphan*/  EC_F_ECPKPARAMETERS_PRINT ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_cofactor (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_GROUP_get0_generator (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_order (int /*<<< orphan*/  const*) ; 
 unsigned char* EC_GROUP_get0_seed (int /*<<< orphan*/  const*) ; 
 scalar_t__ EC_GROUP_get_asn1_flag (int /*<<< orphan*/  const*) ; 
 int EC_GROUP_get_basis_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_get_curve (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ EC_GROUP_get_point_conversion_form (int /*<<< orphan*/  const*) ; 
 size_t EC_GROUP_get_seed_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (int /*<<< orphan*/  const*) ; 
 int EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* EC_POINT_point2bn (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* EC_curve_nid2nist (int) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int) ; 
 int ERR_R_BIO_LIB ; 
 int ERR_R_EC_LIB ; 
 int ERR_R_MALLOC_FAILURE ; 
 int ERR_R_PASSED_NULL_PARAMETER ; 
 int NID_X9_62_characteristic_two_field ; 
 char const* OBJ_nid2sn (int) ; 
 scalar_t__ POINT_CONVERSION_COMPRESSED ; 
 scalar_t__ POINT_CONVERSION_UNCOMPRESSED ; 
 int /*<<< orphan*/  print_bin (int /*<<< orphan*/ *,char*,unsigned char const*,size_t,int) ; 

int ECPKParameters_print(BIO *bp, const EC_GROUP *x, int off)
{
    int ret = 0, reason = ERR_R_BIO_LIB;
    BN_CTX *ctx = NULL;
    const EC_POINT *point = NULL;
    BIGNUM *p = NULL, *a = NULL, *b = NULL, *gen = NULL;
    const BIGNUM *order = NULL, *cofactor = NULL;
    const unsigned char *seed;
    size_t seed_len = 0;

    static const char *gen_compressed = "Generator (compressed):";
    static const char *gen_uncompressed = "Generator (uncompressed):";
    static const char *gen_hybrid = "Generator (hybrid):";

    if (!x) {
        reason = ERR_R_PASSED_NULL_PARAMETER;
        goto err;
    }

    ctx = BN_CTX_new();
    if (ctx == NULL) {
        reason = ERR_R_MALLOC_FAILURE;
        goto err;
    }

    if (EC_GROUP_get_asn1_flag(x)) {
        /* the curve parameter are given by an asn1 OID */
        int nid;
        const char *nname;

        if (!BIO_indent(bp, off, 128))
            goto err;

        nid = EC_GROUP_get_curve_name(x);
        if (nid == 0)
            goto err;
        if (BIO_printf(bp, "ASN1 OID: %s", OBJ_nid2sn(nid)) <= 0)
            goto err;
        if (BIO_printf(bp, "\n") <= 0)
            goto err;
        nname = EC_curve_nid2nist(nid);
        if (nname) {
            if (!BIO_indent(bp, off, 128))
                goto err;
            if (BIO_printf(bp, "NIST CURVE: %s\n", nname) <= 0)
                goto err;
        }
    } else {
        /* explicit parameters */
        int is_char_two = 0;
        point_conversion_form_t form;
        int tmp_nid = EC_METHOD_get_field_type(EC_GROUP_method_of(x));

        if (tmp_nid == NID_X9_62_characteristic_two_field)
            is_char_two = 1;

        if ((p = BN_new()) == NULL || (a = BN_new()) == NULL ||
            (b = BN_new()) == NULL) {
            reason = ERR_R_MALLOC_FAILURE;
            goto err;
        }

        if (!EC_GROUP_get_curve(x, p, a, b, ctx)) {
            reason = ERR_R_EC_LIB;
            goto err;
        }

        if ((point = EC_GROUP_get0_generator(x)) == NULL) {
            reason = ERR_R_EC_LIB;
            goto err;
        }
        order = EC_GROUP_get0_order(x);
        cofactor = EC_GROUP_get0_cofactor(x);
        if (order == NULL) {
            reason = ERR_R_EC_LIB;
            goto err;
        }

        form = EC_GROUP_get_point_conversion_form(x);

        if ((gen = EC_POINT_point2bn(x, point, form, NULL, ctx)) == NULL) {
            reason = ERR_R_EC_LIB;
            goto err;
        }

        if ((seed = EC_GROUP_get0_seed(x)) != NULL)
            seed_len = EC_GROUP_get_seed_len(x);

        if (!BIO_indent(bp, off, 128))
            goto err;

        /* print the 'short name' of the field type */
        if (BIO_printf(bp, "Field Type: %s\n", OBJ_nid2sn(tmp_nid))
            <= 0)
            goto err;

        if (is_char_two) {
            /* print the 'short name' of the base type OID */
            int basis_type = EC_GROUP_get_basis_type(x);
            if (basis_type == 0)
                goto err;

            if (!BIO_indent(bp, off, 128))
                goto err;

            if (BIO_printf(bp, "Basis Type: %s\n",
                           OBJ_nid2sn(basis_type)) <= 0)
                goto err;

            /* print the polynomial */
            if ((p != NULL) && !ASN1_bn_print(bp, "Polynomial:", p, NULL,
                                              off))
                goto err;
        } else {
            if ((p != NULL) && !ASN1_bn_print(bp, "Prime:", p, NULL, off))
                goto err;
        }
        if ((a != NULL) && !ASN1_bn_print(bp, "A:   ", a, NULL, off))
            goto err;
        if ((b != NULL) && !ASN1_bn_print(bp, "B:   ", b, NULL, off))
            goto err;
        if (form == POINT_CONVERSION_COMPRESSED) {
            if ((gen != NULL) && !ASN1_bn_print(bp, gen_compressed, gen,
                                                NULL, off))
                goto err;
        } else if (form == POINT_CONVERSION_UNCOMPRESSED) {
            if ((gen != NULL) && !ASN1_bn_print(bp, gen_uncompressed, gen,
                                                NULL, off))
                goto err;
        } else {                /* form == POINT_CONVERSION_HYBRID */

            if ((gen != NULL) && !ASN1_bn_print(bp, gen_hybrid, gen,
                                                NULL, off))
                goto err;
        }
        if ((order != NULL) && !ASN1_bn_print(bp, "Order: ", order,
                                              NULL, off))
            goto err;
        if ((cofactor != NULL) && !ASN1_bn_print(bp, "Cofactor: ", cofactor,
                                                 NULL, off))
            goto err;
        if (seed && !print_bin(bp, "Seed:", seed, seed_len, off))
            goto err;
    }
    ret = 1;
 err:
    if (!ret)
        ECerr(EC_F_ECPKPARAMETERS_PRINT, reason);
    BN_free(p);
    BN_free(a);
    BN_free(b);
    BN_free(gen);
    BN_CTX_free(ctx);
    return ret;
}