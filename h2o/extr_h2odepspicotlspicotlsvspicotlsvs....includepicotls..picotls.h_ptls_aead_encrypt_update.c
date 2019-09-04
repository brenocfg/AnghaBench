#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t (* do_encrypt_update ) (TYPE_1__*,void*,void const*,size_t) ;} ;
typedef  TYPE_1__ ptls_aead_context_t ;

/* Variables and functions */
 size_t stub1 (TYPE_1__*,void*,void const*,size_t) ; 

inline size_t ptls_aead_encrypt_update(ptls_aead_context_t *ctx, void *output, const void *input, size_t inlen)
{
    return ctx->do_encrypt_update(ctx, output, input, inlen);
}