#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * parameters; int /*<<< orphan*/ * named_curve; } ;
struct TYPE_8__ {int type; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_2__ ECPKPARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECPARAMETERS_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECPKPARAMETERS_free (TYPE_2__*) ; 
 TYPE_2__* ECPKPARAMETERS_new () ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_GET_ECPKPARAMETERS ; 
 scalar_t__ EC_GROUP_get_asn1_flag (int /*<<< orphan*/  const*) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_GROUP_get_ecparameters (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 

ECPKPARAMETERS *EC_GROUP_get_ecpkparameters(const EC_GROUP *group,
                                            ECPKPARAMETERS *params)
{
    int ok = 1, tmp;
    ECPKPARAMETERS *ret = params;

    if (ret == NULL) {
        if ((ret = ECPKPARAMETERS_new()) == NULL) {
            ECerr(EC_F_EC_GROUP_GET_ECPKPARAMETERS, ERR_R_MALLOC_FAILURE);
            return NULL;
        }
    } else {
        if (ret->type == 0)
            ASN1_OBJECT_free(ret->value.named_curve);
        else if (ret->type == 1 && ret->value.parameters)
            ECPARAMETERS_free(ret->value.parameters);
    }

    if (EC_GROUP_get_asn1_flag(group)) {
        /*
         * use the asn1 OID to describe the elliptic curve parameters
         */
        tmp = EC_GROUP_get_curve_name(group);
        if (tmp) {
            ret->type = 0;
            if ((ret->value.named_curve = OBJ_nid2obj(tmp)) == NULL)
                ok = 0;
        } else
            /* we don't know the nid => ERROR */
            ok = 0;
    } else {
        /* use the ECPARAMETERS structure */
        ret->type = 1;
        if ((ret->value.parameters =
             EC_GROUP_get_ecparameters(group, NULL)) == NULL)
            ok = 0;
    }

    if (!ok) {
        ECPKPARAMETERS_free(ret);
        return NULL;
    }
    return ret;
}