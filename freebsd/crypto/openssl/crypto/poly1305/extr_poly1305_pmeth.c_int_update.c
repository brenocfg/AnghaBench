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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ POLY1305_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_pkey_ctx (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Poly1305_Update (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static int int_update(EVP_MD_CTX *ctx, const void *data, size_t count)
{
    POLY1305_PKEY_CTX *pctx = EVP_PKEY_CTX_get_data(EVP_MD_CTX_pkey_ctx(ctx));

    Poly1305_Update(&pctx->ctx, data, count);
    return 1;
}