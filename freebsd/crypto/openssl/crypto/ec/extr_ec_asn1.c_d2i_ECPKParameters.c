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
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  ECPKPARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  ECPKPARAMETERS_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_D2I_ECPKPARAMETERS ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_from_ecpkparameters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_D2I_ECPKPARAMETERS_FAILURE ; 
 int /*<<< orphan*/  EC_R_PKPARAMETERS2GROUP_FAILURE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_ECPKPARAMETERS (int /*<<< orphan*/ *,unsigned char const**,long) ; 

EC_GROUP *d2i_ECPKParameters(EC_GROUP **a, const unsigned char **in, long len)
{
    EC_GROUP *group = NULL;
    ECPKPARAMETERS *params = NULL;
    const unsigned char *p = *in;

    if ((params = d2i_ECPKPARAMETERS(NULL, &p, len)) == NULL) {
        ECerr(EC_F_D2I_ECPKPARAMETERS, EC_R_D2I_ECPKPARAMETERS_FAILURE);
        ECPKPARAMETERS_free(params);
        return NULL;
    }

    if ((group = EC_GROUP_new_from_ecpkparameters(params)) == NULL) {
        ECerr(EC_F_D2I_ECPKPARAMETERS, EC_R_PKPARAMETERS2GROUP_FAILURE);
        ECPKPARAMETERS_free(params);
        return NULL;
    }

    if (a) {
        EC_GROUP_free(*a);
        *a = group;
    }

    ECPKPARAMETERS_free(params);
    *in = p;
    return group;
}