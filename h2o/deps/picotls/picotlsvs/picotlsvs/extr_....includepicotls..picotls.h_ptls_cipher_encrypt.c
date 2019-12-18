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
struct TYPE_4__ {int /*<<< orphan*/  (* do_transform ) (TYPE_1__*,void*,void const*,size_t) ;} ;
typedef  TYPE_1__ ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,void const*,size_t) ; 

inline void ptls_cipher_encrypt(ptls_cipher_context_t *ctx, void *output, const void *input, size_t len)
{
    ctx->do_transform(ctx, output, input, len);
}