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
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int N; int r; int p; int maxmem_bytes; } ;
typedef  TYPE_1__ SCRYPT_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  KDF_F_PKEY_SCRYPT_INIT ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int pkey_scrypt_init(EVP_PKEY_CTX *ctx)
{
    SCRYPT_PKEY_CTX *kctx;

    kctx = OPENSSL_zalloc(sizeof(*kctx));
    if (kctx == NULL) {
        KDFerr(KDF_F_PKEY_SCRYPT_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    /* Default values are the most conservative recommendation given in the
     * original paper of C. Percival. Derivation uses roughly 1 GiB of memory
     * for this parameter choice (approx. 128 * r * (N + p) bytes).
     */
    kctx->N = 1 << 20;
    kctx->r = 8;
    kctx->p = 1;
    kctx->maxmem_bytes = 1025 * 1024 * 1024;

    ctx->data = kctx;

    return 1;
}