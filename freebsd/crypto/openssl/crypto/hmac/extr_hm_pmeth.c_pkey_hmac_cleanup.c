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
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ ktmp; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ HMAC_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 TYPE_2__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 

__attribute__((used)) static void pkey_hmac_cleanup(EVP_PKEY_CTX *ctx)
{
    HMAC_PKEY_CTX *hctx = EVP_PKEY_CTX_get_data(ctx);

    if (hctx != NULL) {
        HMAC_CTX_free(hctx->ctx);
        OPENSSL_clear_free(hctx->ktmp.data, hctx->ktmp.length);
        OPENSSL_free(hctx);
        EVP_PKEY_CTX_set_data(ctx, NULL);
    }
}