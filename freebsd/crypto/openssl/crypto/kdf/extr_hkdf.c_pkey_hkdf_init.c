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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  HKDF_PKEY_CTX ;
typedef  TYPE_1__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  KDF_F_PKEY_HKDF_INIT ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

__attribute__((used)) static int pkey_hkdf_init(EVP_PKEY_CTX *ctx)
{
    HKDF_PKEY_CTX *kctx;

    if ((kctx = OPENSSL_zalloc(sizeof(*kctx))) == NULL) {
        KDFerr(KDF_F_PKEY_HKDF_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    ctx->data = kctx;

    return 1;
}