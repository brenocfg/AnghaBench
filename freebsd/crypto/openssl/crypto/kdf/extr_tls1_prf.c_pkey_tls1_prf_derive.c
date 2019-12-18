#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {scalar_t__ seedlen; int /*<<< orphan*/  seed; int /*<<< orphan*/  seclen; int /*<<< orphan*/ * sec; int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ TLS1_PRF_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  KDF_F_PKEY_TLS1_PRF_DERIVE ; 
 int /*<<< orphan*/  KDF_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  KDF_R_MISSING_SECRET ; 
 int /*<<< orphan*/  KDF_R_MISSING_SEED ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tls1_prf_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned char*,size_t) ; 

__attribute__((used)) static int pkey_tls1_prf_derive(EVP_PKEY_CTX *ctx, unsigned char *key,
                                size_t *keylen)
{
    TLS1_PRF_PKEY_CTX *kctx = ctx->data;
    if (kctx->md == NULL) {
        KDFerr(KDF_F_PKEY_TLS1_PRF_DERIVE, KDF_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    if (kctx->sec == NULL) {
        KDFerr(KDF_F_PKEY_TLS1_PRF_DERIVE, KDF_R_MISSING_SECRET);
        return 0;
    }
    if (kctx->seedlen == 0) {
        KDFerr(KDF_F_PKEY_TLS1_PRF_DERIVE, KDF_R_MISSING_SEED);
        return 0;
    }
    return tls1_prf_alg(kctx->md, kctx->sec, kctx->seclen,
                        kctx->seed, kctx->seedlen,
                        key, *keylen);
}