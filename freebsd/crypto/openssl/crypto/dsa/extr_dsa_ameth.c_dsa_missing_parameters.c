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
struct TYPE_7__ {int /*<<< orphan*/ * g; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
struct TYPE_5__ {TYPE_3__* dsa; } ;
struct TYPE_6__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ DSA ;

/* Variables and functions */

__attribute__((used)) static int dsa_missing_parameters(const EVP_PKEY *pkey)
{
    DSA *dsa;
    dsa = pkey->pkey.dsa;
    if (dsa == NULL || dsa->p == NULL || dsa->q == NULL || dsa->g == NULL)
        return 1;
    return 0;
}