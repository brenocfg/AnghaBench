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
struct TYPE_3__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  ktmp; } ;
typedef  TYPE_1__ SIPHASH_PKEY_CTX ;
typedef  int /*<<< orphan*/  SIPHASH ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pkey_siphash_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkey_siphash_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_siphash_copy(EVP_PKEY_CTX *dst, EVP_PKEY_CTX *src)
{
    SIPHASH_PKEY_CTX *sctx, *dctx;

    /* allocate memory for dst->data and a new SIPHASH_CTX in dst->data->ctx */
    if (!pkey_siphash_init(dst))
        return 0;
    sctx = EVP_PKEY_CTX_get_data(src);
    dctx = EVP_PKEY_CTX_get_data(dst);
    if (ASN1_STRING_get0_data(&sctx->ktmp) != NULL &&
        !ASN1_STRING_copy(&dctx->ktmp, &sctx->ktmp)) {
        /* cleanup and free the SIPHASH_PKEY_CTX in dst->data */
        pkey_siphash_cleanup(dst);
        return 0;
    }
    memcpy(&dctx->ctx, &sctx->ctx, sizeof(SIPHASH));
    return 1;
}