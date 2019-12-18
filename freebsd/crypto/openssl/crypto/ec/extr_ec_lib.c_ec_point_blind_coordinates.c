#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* meth; } ;
struct TYPE_5__ {int (* blind_coordinates ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_point_blind_coordinates(const EC_GROUP *group, EC_POINT *p, BN_CTX *ctx)
{
    if (group->meth->blind_coordinates == NULL)
        return 1; /* ignore if not implemented */

    return group->meth->blind_coordinates(group, p, ctx);
}