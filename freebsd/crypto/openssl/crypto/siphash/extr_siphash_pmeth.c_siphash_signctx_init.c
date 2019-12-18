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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ SIPHASH_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NO_INIT ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_update_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_get0_pkey (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 unsigned char* EVP_PKEY_get0_siphash (int /*<<< orphan*/ ,size_t*) ; 
 size_t SIPHASH_KEY_SIZE ; 
 int SipHash_Init (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_update ; 

__attribute__((used)) static int siphash_signctx_init(EVP_PKEY_CTX *ctx, EVP_MD_CTX *mctx)
{
    SIPHASH_PKEY_CTX *pctx = EVP_PKEY_CTX_get_data(ctx);
    const unsigned char* key;
    size_t len;

    key = EVP_PKEY_get0_siphash(EVP_PKEY_CTX_get0_pkey(ctx), &len);
    if (key == NULL || len != SIPHASH_KEY_SIZE)
        return 0;
    EVP_MD_CTX_set_flags(mctx, EVP_MD_CTX_FLAG_NO_INIT);
    EVP_MD_CTX_set_update_fn(mctx, int_update);
    return SipHash_Init(&pctx->ctx, key, 0, 0);
}