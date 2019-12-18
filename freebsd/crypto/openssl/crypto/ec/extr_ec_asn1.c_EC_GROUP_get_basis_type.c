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
struct TYPE_4__ {scalar_t__* poly; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_method_of (TYPE_1__ const*) ; 
 scalar_t__ EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 scalar_t__ NID_X9_62_characteristic_two_field ; 
 int NID_X9_62_ppBasis ; 
 int NID_X9_62_tpBasis ; 
 scalar_t__ OSSL_NELEM (scalar_t__*) ; 

int EC_GROUP_get_basis_type(const EC_GROUP *group)
{
    int i;

    if (EC_METHOD_get_field_type(EC_GROUP_method_of(group)) !=
        NID_X9_62_characteristic_two_field)
        /* everything else is currently not supported */
        return 0;

    /* Find the last non-zero element of group->poly[] */
    for (i = 0;
         i < (int)OSSL_NELEM(group->poly) && group->poly[i] != 0;
         i++)
        continue;

    if (i == 4)
        return NID_X9_62_ppBasis;
    else if (i == 2)
        return NID_X9_62_tpBasis;
    else
        /* everything else is currently not supported */
        return 0;
}