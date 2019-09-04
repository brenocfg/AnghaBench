#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {size_t (* do_decrypt ) (TYPE_1__*,void*,void const*,size_t,int /*<<< orphan*/ *,void const*,size_t) ;} ;
typedef  TYPE_1__ ptls_aead_context_t ;

/* Variables and functions */
 int PTLS_MAX_IV_SIZE ; 
 int /*<<< orphan*/  ptls_aead__build_iv (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t stub1 (TYPE_1__*,void*,void const*,size_t,int /*<<< orphan*/ *,void const*,size_t) ; 

inline size_t ptls_aead_decrypt(ptls_aead_context_t *ctx, void *output, const void *input, size_t inlen, uint64_t seq,
                                const void *aad, size_t aadlen)
{
    uint8_t iv[PTLS_MAX_IV_SIZE];

    ptls_aead__build_iv(ctx, iv, seq);
    return ctx->do_decrypt(ctx, output, input, inlen, iv, aad, aadlen);
}