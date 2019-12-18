#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ keygen_info_count; TYPE_2__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ctx; TYPE_1__ ktmp; } ;
typedef  TYPE_2__ HMAC_PKEY_CTX ;
typedef  TYPE_3__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_PKEY_HMAC_INIT ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 

__attribute__((used)) static int pkey_hmac_init(EVP_PKEY_CTX *ctx)
{
    HMAC_PKEY_CTX *hctx;

    if ((hctx = OPENSSL_zalloc(sizeof(*hctx))) == NULL) {
        CRYPTOerr(CRYPTO_F_PKEY_HMAC_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    hctx->ktmp.type = V_ASN1_OCTET_STRING;
    hctx->ctx = HMAC_CTX_new();
    if (hctx->ctx == NULL) {
        OPENSSL_free(hctx);
        return 0;
    }

    ctx->data = hctx;
    ctx->keygen_info_count = 0;

    return 1;
}