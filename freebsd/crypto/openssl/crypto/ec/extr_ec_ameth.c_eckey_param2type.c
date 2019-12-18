#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_STRING_new () ; 
 int /*<<< orphan*/  EC_F_ECKEY_PARAM2TYPE ; 
 scalar_t__ EC_GROUP_get_asn1_flag (int /*<<< orphan*/  const*) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 void* OBJ_nid2obj (int) ; 
 int V_ASN1_OBJECT ; 
 int V_ASN1_SEQUENCE ; 
 scalar_t__ i2d_ECParameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eckey_param2type(int *pptype, void **ppval, EC_KEY *ec_key)
{
    const EC_GROUP *group;
    int nid;
    if (ec_key == NULL || (group = EC_KEY_get0_group(ec_key)) == NULL) {
        ECerr(EC_F_ECKEY_PARAM2TYPE, EC_R_MISSING_PARAMETERS);
        return 0;
    }
    if (EC_GROUP_get_asn1_flag(group)
        && (nid = EC_GROUP_get_curve_name(group)))
        /* we have a 'named curve' => just set the OID */
    {
        *ppval = OBJ_nid2obj(nid);
        *pptype = V_ASN1_OBJECT;
    } else {                    /* explicit parameters */

        ASN1_STRING *pstr = NULL;
        pstr = ASN1_STRING_new();
        if (pstr == NULL)
            return 0;
        pstr->length = i2d_ECParameters(ec_key, &pstr->data);
        if (pstr->length <= 0) {
            ASN1_STRING_free(pstr);
            ECerr(EC_F_ECKEY_PARAM2TYPE, ERR_R_EC_LIB);
            return 0;
        }
        *ppval = pstr;
        *pptype = V_ASN1_SEQUENCE;
    }
    return 1;
}