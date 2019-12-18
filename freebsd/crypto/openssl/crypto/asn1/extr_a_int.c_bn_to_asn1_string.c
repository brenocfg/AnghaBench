#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; int length; scalar_t__* data; } ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  TYPE_1__ ASN1_STRING ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_BN_TO_ASN1_STRING ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (TYPE_1__*) ; 
 scalar_t__ ASN1_STRING_set (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ASN1_STRING_type_new (int) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BN_bn2bin (int /*<<< orphan*/  const*,scalar_t__*) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_NESTED_ASN1_ERROR ; 
 int V_ASN1_NEG_INTEGER ; 

__attribute__((used)) static ASN1_STRING *bn_to_asn1_string(const BIGNUM *bn, ASN1_STRING *ai,
                                      int atype)
{
    ASN1_INTEGER *ret;
    int len;

    if (ai == NULL) {
        ret = ASN1_STRING_type_new(atype);
    } else {
        ret = ai;
        ret->type = atype;
    }

    if (ret == NULL) {
        ASN1err(ASN1_F_BN_TO_ASN1_STRING, ERR_R_NESTED_ASN1_ERROR);
        goto err;
    }

    if (BN_is_negative(bn) && !BN_is_zero(bn))
        ret->type |= V_ASN1_NEG_INTEGER;

    len = BN_num_bytes(bn);

    if (len == 0)
        len = 1;

    if (ASN1_STRING_set(ret, NULL, len) == 0) {
        ASN1err(ASN1_F_BN_TO_ASN1_STRING, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* Correct zero case */
    if (BN_is_zero(bn))
        ret->data[0] = 0;
    else
        len = BN_bn2bin(bn, ret->data);
    ret->length = len;
    return ret;
 err:
    if (ret != ai)
        ASN1_INTEGER_free(ret);
    return NULL;
}