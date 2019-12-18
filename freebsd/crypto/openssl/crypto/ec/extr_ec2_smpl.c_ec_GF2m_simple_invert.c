#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int BN_GF2m_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ EC_POINT_is_at_infinity (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  EC_POINT_make_affine (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *) ; 

int ec_GF2m_simple_invert(const EC_GROUP *group, EC_POINT *point, BN_CTX *ctx)
{
    if (EC_POINT_is_at_infinity(group, point) || BN_is_zero(point->Y))
        /* point is its own inverse */
        return 1;

    if (!EC_POINT_make_affine(group, point, ctx))
        return 0;
    return BN_GF2m_add(point->Y, point->X, point->Y);
}