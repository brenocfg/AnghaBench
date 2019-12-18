#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_ptls_cipher_context_t {int dummy; } ;
struct TYPE_3__ {scalar_t__ do_init; } ;
struct TYPE_4__ {int /*<<< orphan*/  tweaks; TYPE_1__ super; } ;
typedef  TYPE_2__ ptls_ffx_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static void ffx_init(struct st_ptls_cipher_context_t *_ctx, const void *iv)
{
    ptls_ffx_context_t *ctx = (ptls_ffx_context_t *)_ctx;
    assert(ctx->super.do_init == ffx_init);
    memcpy(ctx->tweaks, iv, 16);
}