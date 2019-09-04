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
struct TYPE_5__ {int /*<<< orphan*/  (* do_encrypt_init ) (TYPE_1__*,int /*<<< orphan*/ *,void const*,size_t) ;} ;
typedef  TYPE_1__ ptls_aead_context_t ;

/* Variables and functions */
 int PTLS_MAX_IV_SIZE ; 
 int /*<<< orphan*/  ptls_aead__build_iv (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,void const*,size_t) ; 

inline void ptls_aead_encrypt_init(ptls_aead_context_t *ctx, uint64_t seq, const void *aad, size_t aadlen)
{
    uint8_t iv[PTLS_MAX_IV_SIZE];

    ptls_aead__build_iv(ctx, iv, seq);
    ctx->do_encrypt_init(ctx, iv, aad, aadlen);
}