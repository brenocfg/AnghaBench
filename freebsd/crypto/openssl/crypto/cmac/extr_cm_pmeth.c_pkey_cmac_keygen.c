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
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  CMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMAC_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CMAC_CTX_new () ; 
 int /*<<< orphan*/  EVP_PKEY_CMAC ; 
 int /*<<< orphan*/  EVP_PKEY_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_cmac_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    CMAC_CTX *cmkey = CMAC_CTX_new();
    CMAC_CTX *cmctx = ctx->data;
    if (cmkey == NULL)
        return 0;
    if (!CMAC_CTX_copy(cmkey, cmctx)) {
        CMAC_CTX_free(cmkey);
        return 0;
    }
    EVP_PKEY_assign(pkey, EVP_PKEY_CMAC, cmkey);

    return 1;
}