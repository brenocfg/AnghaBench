#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; TYPE_1__* ameth; } ;
struct TYPE_11__ {int (* param_copy ) (TYPE_2__ const*,TYPE_2__ const*) ;} ;
typedef  TYPE_2__ const EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_COPY_PARAMETERS ; 
 scalar_t__ EVP_PKEY_NONE ; 
 int EVP_PKEY_cmp_parameters (TYPE_2__ const*,TYPE_2__ const*) ; 
 scalar_t__ EVP_PKEY_missing_parameters (TYPE_2__ const*) ; 
 scalar_t__ EVP_PKEY_set_type (TYPE_2__ const*,scalar_t__) ; 
 int /*<<< orphan*/  EVP_R_DIFFERENT_KEY_TYPES ; 
 int /*<<< orphan*/  EVP_R_DIFFERENT_PARAMETERS ; 
 int /*<<< orphan*/  EVP_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__ const*,TYPE_2__ const*) ; 

int EVP_PKEY_copy_parameters(EVP_PKEY *to, const EVP_PKEY *from)
{
    if (to->type == EVP_PKEY_NONE) {
        if (EVP_PKEY_set_type(to, from->type) == 0)
            return 0;
    } else if (to->type != from->type) {
        EVPerr(EVP_F_EVP_PKEY_COPY_PARAMETERS, EVP_R_DIFFERENT_KEY_TYPES);
        goto err;
    }

    if (EVP_PKEY_missing_parameters(from)) {
        EVPerr(EVP_F_EVP_PKEY_COPY_PARAMETERS, EVP_R_MISSING_PARAMETERS);
        goto err;
    }

    if (!EVP_PKEY_missing_parameters(to)) {
        if (EVP_PKEY_cmp_parameters(to, from) == 1)
            return 1;
        EVPerr(EVP_F_EVP_PKEY_COPY_PARAMETERS, EVP_R_DIFFERENT_PARAMETERS);
        return 0;
    }

    if (from->ameth && from->ameth->param_copy)
        return from->ameth->param_copy(to, from);
 err:
    return 0;
}