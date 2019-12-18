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
struct TYPE_4__ {int /*<<< orphan*/  maxmem_bytes; int /*<<< orphan*/  p; int /*<<< orphan*/  r; int /*<<< orphan*/  N; int /*<<< orphan*/  salt_len; int /*<<< orphan*/ * salt; int /*<<< orphan*/  pass_len; int /*<<< orphan*/ * pass; } ;
typedef  TYPE_1__ SCRYPT_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int EVP_PBE_scrypt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  KDF_F_PKEY_SCRYPT_DERIVE ; 
 int /*<<< orphan*/  KDF_R_MISSING_PASS ; 
 int /*<<< orphan*/  KDF_R_MISSING_SALT ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_scrypt_derive(EVP_PKEY_CTX *ctx, unsigned char *key,
                              size_t *keylen)
{
    SCRYPT_PKEY_CTX *kctx = ctx->data;

    if (kctx->pass == NULL) {
        KDFerr(KDF_F_PKEY_SCRYPT_DERIVE, KDF_R_MISSING_PASS);
        return 0;
    }

    if (kctx->salt == NULL) {
        KDFerr(KDF_F_PKEY_SCRYPT_DERIVE, KDF_R_MISSING_SALT);
        return 0;
    }

    return EVP_PBE_scrypt((char *)kctx->pass, kctx->pass_len, kctx->salt,
                          kctx->salt_len, kctx->N, kctx->r, kctx->p,
                          kctx->maxmem_bytes, key, *keylen);
}