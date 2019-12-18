#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* group; } ;
struct TYPE_6__ {TYPE_1__* meth; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_3__ EC_KEY ;

/* Variables and functions */
 int EC_FLAGS_NO_SIGN ; 

int EC_KEY_can_sign(const EC_KEY *eckey)
{
    if (eckey->group == NULL || eckey->group->meth == NULL
        || (eckey->group->meth->flags & EC_FLAGS_NO_SIGN))
        return 0;
    return 1;
}