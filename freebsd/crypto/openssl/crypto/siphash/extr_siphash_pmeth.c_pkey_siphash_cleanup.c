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
struct TYPE_5__ {int length; TYPE_2__* data; } ;
struct TYPE_6__ {TYPE_1__ ktmp; } ;
typedef  TYPE_2__ SIPHASH_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 TYPE_2__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (TYPE_2__*,int) ; 

__attribute__((used)) static void pkey_siphash_cleanup(EVP_PKEY_CTX *ctx)
{
    SIPHASH_PKEY_CTX *pctx = EVP_PKEY_CTX_get_data(ctx);

    if (pctx != NULL) {
        OPENSSL_clear_free(pctx->ktmp.data, pctx->ktmp.length);
        OPENSSL_clear_free(pctx, sizeof(*pctx));
        EVP_PKEY_CTX_set_data(ctx, NULL);
    }
}