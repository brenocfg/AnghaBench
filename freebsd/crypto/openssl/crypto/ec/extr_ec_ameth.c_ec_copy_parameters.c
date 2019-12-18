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
struct TYPE_5__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_6__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_GROUP_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new () ; 
 scalar_t__ EC_KEY_set_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ec_copy_parameters(EVP_PKEY *to, const EVP_PKEY *from)
{
    EC_GROUP *group = EC_GROUP_dup(EC_KEY_get0_group(from->pkey.ec));

    if (group == NULL)
        return 0;
    if (to->pkey.ec == NULL) {
        to->pkey.ec = EC_KEY_new();
        if (to->pkey.ec == NULL)
            goto err;
    }
    if (EC_KEY_set_group(to->pkey.ec, group) == 0)
        goto err;
    EC_GROUP_free(group);
    return 1;
 err:
    EC_GROUP_free(group);
    return 0;
}