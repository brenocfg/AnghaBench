#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  length; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_3__ ktmp; int /*<<< orphan*/  ctx; int /*<<< orphan*/  md; } ;
typedef  TYPE_1__ HMAC_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_hmac_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkey_hmac_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_hmac_copy(EVP_PKEY_CTX *dst, EVP_PKEY_CTX *src)
{
    HMAC_PKEY_CTX *sctx, *dctx;

    /* allocate memory for dst->data and a new HMAC_CTX in dst->data->ctx */
    if (!pkey_hmac_init(dst))
        return 0;
    sctx = EVP_PKEY_CTX_get_data(src);
    dctx = EVP_PKEY_CTX_get_data(dst);
    dctx->md = sctx->md;
    if (!HMAC_CTX_copy(dctx->ctx, sctx->ctx))
        goto err;
    if (sctx->ktmp.data) {
        if (!ASN1_OCTET_STRING_set(&dctx->ktmp,
                                   sctx->ktmp.data, sctx->ktmp.length))
            goto err;
    }
    return 1;
err:
    /* release HMAC_CTX in dst->data->ctx and memory allocated for dst->data */
    pkey_hmac_cleanup (dst);
    return 0;
}