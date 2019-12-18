#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  const* md; } ;
typedef  TYPE_1__ TLS1_PRF_PKEY_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTRL_TLS_SECRET ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_TLS_SEED ; 
 int EVP_PKEY_CTX_hex2ctrl (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int EVP_PKEY_CTX_str2ctrl (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 int /*<<< orphan*/  KDF_F_PKEY_TLS1_PRF_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_INVALID_DIGEST ; 
 int /*<<< orphan*/  KDF_R_UNKNOWN_PARAMETER_TYPE ; 
 int /*<<< orphan*/  KDF_R_VALUE_MISSING ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_tls1_prf_ctrl_str(EVP_PKEY_CTX *ctx,
                                  const char *type, const char *value)
{
    if (value == NULL) {
        KDFerr(KDF_F_PKEY_TLS1_PRF_CTRL_STR, KDF_R_VALUE_MISSING);
        return 0;
    }
    if (strcmp(type, "md") == 0) {
        TLS1_PRF_PKEY_CTX *kctx = ctx->data;

        const EVP_MD *md = EVP_get_digestbyname(value);
        if (md == NULL) {
            KDFerr(KDF_F_PKEY_TLS1_PRF_CTRL_STR, KDF_R_INVALID_DIGEST);
            return 0;
        }
        kctx->md = md;
        return 1;
    }
    if (strcmp(type, "secret") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_TLS_SECRET, value);
    if (strcmp(type, "hexsecret") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_TLS_SECRET, value);
    if (strcmp(type, "seed") == 0)
        return EVP_PKEY_CTX_str2ctrl(ctx, EVP_PKEY_CTRL_TLS_SEED, value);
    if (strcmp(type, "hexseed") == 0)
        return EVP_PKEY_CTX_hex2ctrl(ctx, EVP_PKEY_CTRL_TLS_SEED, value);

    KDFerr(KDF_F_PKEY_TLS1_PRF_CTRL_STR, KDF_R_UNKNOWN_PARAMETER_TYPE);
    return -2;
}