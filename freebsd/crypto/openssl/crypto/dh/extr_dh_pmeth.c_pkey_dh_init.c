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
struct TYPE_6__ {int prime_len; int subprime_len; int generator; int /*<<< orphan*/  gentmp; int /*<<< orphan*/  kdf_type; } ;
struct TYPE_5__ {int keygen_info_count; int /*<<< orphan*/  keygen_info; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ DH_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DH_F_PKEY_DH_INIT ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_DH_KDF_NONE ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int pkey_dh_init(EVP_PKEY_CTX *ctx)
{
    DH_PKEY_CTX *dctx;

    if ((dctx = OPENSSL_zalloc(sizeof(*dctx))) == NULL) {
        DHerr(DH_F_PKEY_DH_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    dctx->prime_len = 2048;
    dctx->subprime_len = -1;
    dctx->generator = 2;
    dctx->kdf_type = EVP_PKEY_DH_KDF_NONE;

    ctx->data = dctx;
    ctx->keygen_info = dctx->gentmp;
    ctx->keygen_info_count = 2;

    return 1;
}