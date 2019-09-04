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
struct TYPE_4__ {int /*<<< orphan*/  (* do_init ) (TYPE_1__*,void const*) ;} ;
typedef  TYPE_1__ ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void const*) ; 

inline void ptls_cipher_init(ptls_cipher_context_t *ctx, const void *iv)
{
    ctx->do_init(ctx, iv);
}