#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * default_policy; } ;
typedef  TYPE_1__ TS_RESP_CTX ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OBJ_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TS_F_TS_RESP_CTX_SET_DEF_POLICY ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_RESP_CTX_set_def_policy(TS_RESP_CTX *ctx, const ASN1_OBJECT *def_policy)
{
    ASN1_OBJECT_free(ctx->default_policy);
    if ((ctx->default_policy = OBJ_dup(def_policy)) == NULL)
        goto err;
    return 1;
 err:
    TSerr(TS_F_TS_RESP_CTX_SET_DEF_POLICY, ERR_R_MALLOC_FAILURE);
    return 0;
}