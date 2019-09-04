#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  nonce; scalar_t__ ncounter; scalar_t__ nblock; } ;
struct chacha20_context_t {TYPE_1__ chacha; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static void chacha20_init(ptls_cipher_context_t *_ctx, const void *iv)
{
    struct chacha20_context_t *ctx = (struct chacha20_context_t *)_ctx;
    ctx->chacha.nblock = 0;
    ctx->chacha.ncounter = 0;
    memcpy(ctx->chacha.nonce, iv, sizeof ctx->chacha.nonce);
}