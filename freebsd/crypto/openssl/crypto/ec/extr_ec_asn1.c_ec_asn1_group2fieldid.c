#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* char_two; int /*<<< orphan*/ * prime; int /*<<< orphan*/  other; } ;
struct TYPE_10__ {TYPE_1__ p; int /*<<< orphan*/ * fieldType; } ;
typedef  TYPE_3__ X9_62_FIELDID ;
struct TYPE_9__ {int /*<<< orphan*/ * onBasis; TYPE_6__* ppBasis; int /*<<< orphan*/ * tpBasis; } ;
struct TYPE_11__ {long m; TYPE_2__ p; int /*<<< orphan*/ * type; } ;
typedef  TYPE_4__ X9_62_CHARACTERISTIC_TWO ;
struct TYPE_12__ {long k1; long k2; long k3; } ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/ * ASN1_NULL_new () ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/ * BN_to_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_ASN1_GROUP2FIELDID ; 
 int EC_GROUP_get_basis_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_get_curve (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_GROUP_get_degree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_get_pentanomial_basis (int /*<<< orphan*/  const*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  EC_GROUP_get_trinomial_basis (int /*<<< orphan*/  const*,unsigned int*) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (int /*<<< orphan*/  const*) ; 
 int EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_R_GF2M_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EC_R_UNSUPPORTED_FIELD ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_OBJ_LIB ; 
 int NID_X9_62_characteristic_two_field ; 
 int NID_X9_62_ppBasis ; 
 int NID_X9_62_prime_field ; 
 int NID_X9_62_tpBasis ; 
 void* OBJ_nid2obj (int) ; 
 TYPE_4__* X9_62_CHARACTERISTIC_TWO_new () ; 
 TYPE_6__* X9_62_PENTANOMIAL_new () ; 

__attribute__((used)) static int ec_asn1_group2fieldid(const EC_GROUP *group, X9_62_FIELDID *field)
{
    int ok = 0, nid;
    BIGNUM *tmp = NULL;

    if (group == NULL || field == NULL)
        return 0;

    /* clear the old values (if necessary) */
    ASN1_OBJECT_free(field->fieldType);
    ASN1_TYPE_free(field->p.other);

    nid = EC_METHOD_get_field_type(EC_GROUP_method_of(group));
    /* set OID for the field */
    if ((field->fieldType = OBJ_nid2obj(nid)) == NULL) {
        ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_OBJ_LIB);
        goto err;
    }

    if (nid == NID_X9_62_prime_field) {
        if ((tmp = BN_new()) == NULL) {
            ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        /* the parameters are specified by the prime number p */
        if (!EC_GROUP_get_curve(group, tmp, NULL, NULL, NULL)) {
            ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_EC_LIB);
            goto err;
        }
        /* set the prime number */
        field->p.prime = BN_to_ASN1_INTEGER(tmp, NULL);
        if (field->p.prime == NULL) {
            ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_ASN1_LIB);
            goto err;
        }
    } else if (nid == NID_X9_62_characteristic_two_field)
#ifdef OPENSSL_NO_EC2M
    {
        ECerr(EC_F_EC_ASN1_GROUP2FIELDID, EC_R_GF2M_NOT_SUPPORTED);
        goto err;
    }
#else
    {
        int field_type;
        X9_62_CHARACTERISTIC_TWO *char_two;

        field->p.char_two = X9_62_CHARACTERISTIC_TWO_new();
        char_two = field->p.char_two;

        if (char_two == NULL) {
            ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_MALLOC_FAILURE);
            goto err;
        }

        char_two->m = (long)EC_GROUP_get_degree(group);

        field_type = EC_GROUP_get_basis_type(group);

        if (field_type == 0) {
            ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_EC_LIB);
            goto err;
        }
        /* set base type OID */
        if ((char_two->type = OBJ_nid2obj(field_type)) == NULL) {
            ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_OBJ_LIB);
            goto err;
        }

        if (field_type == NID_X9_62_tpBasis) {
            unsigned int k;

            if (!EC_GROUP_get_trinomial_basis(group, &k))
                goto err;

            char_two->p.tpBasis = ASN1_INTEGER_new();
            if (char_two->p.tpBasis == NULL) {
                ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_MALLOC_FAILURE);
                goto err;
            }
            if (!ASN1_INTEGER_set(char_two->p.tpBasis, (long)k)) {
                ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_ASN1_LIB);
                goto err;
            }
        } else if (field_type == NID_X9_62_ppBasis) {
            unsigned int k1, k2, k3;

            if (!EC_GROUP_get_pentanomial_basis(group, &k1, &k2, &k3))
                goto err;

            char_two->p.ppBasis = X9_62_PENTANOMIAL_new();
            if (char_two->p.ppBasis == NULL) {
                ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_MALLOC_FAILURE);
                goto err;
            }

            /* set k? values */
            char_two->p.ppBasis->k1 = (long)k1;
            char_two->p.ppBasis->k2 = (long)k2;
            char_two->p.ppBasis->k3 = (long)k3;
        } else {                /* field_type == NID_X9_62_onBasis */

            /* for ONB the parameters are (asn1) NULL */
            char_two->p.onBasis = ASN1_NULL_new();
            if (char_two->p.onBasis == NULL) {
                ECerr(EC_F_EC_ASN1_GROUP2FIELDID, ERR_R_MALLOC_FAILURE);
                goto err;
            }
        }
    }
#endif
    else {
        ECerr(EC_F_EC_ASN1_GROUP2FIELDID, EC_R_UNSUPPORTED_FIELD);
        goto err;
    }

    ok = 1;

 err:
    BN_free(tmp);
    return ok;
}