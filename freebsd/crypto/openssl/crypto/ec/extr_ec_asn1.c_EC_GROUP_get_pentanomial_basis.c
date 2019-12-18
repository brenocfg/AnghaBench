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
struct TYPE_4__ {unsigned int* poly; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_EC_GROUP_GET_PENTANOMIAL_BASIS ; 
 int /*<<< orphan*/  EC_GROUP_method_of (TYPE_1__ const*) ; 
 scalar_t__ EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 scalar_t__ NID_X9_62_characteristic_two_field ; 

int EC_GROUP_get_pentanomial_basis(const EC_GROUP *group, unsigned int *k1,
                                   unsigned int *k2, unsigned int *k3)
{
    if (group == NULL)
        return 0;

    if (EC_METHOD_get_field_type(EC_GROUP_method_of(group)) !=
        NID_X9_62_characteristic_two_field
        || !((group->poly[0] != 0) && (group->poly[1] != 0)
             && (group->poly[2] != 0) && (group->poly[3] != 0)
             && (group->poly[4] == 0))) {
        ECerr(EC_F_EC_GROUP_GET_PENTANOMIAL_BASIS,
              ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }

    if (k1)
        *k1 = group->poly[3];
    if (k2)
        *k2 = group->poly[2];
    if (k3)
        *k3 = group->poly[1];

    return 1;
}