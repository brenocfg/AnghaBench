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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  do_transform; int /*<<< orphan*/  do_init; int /*<<< orphan*/  do_dispose; } ;
struct chacha20_context_t {int /*<<< orphan*/  chacha; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CHACHA20_KEY_SIZE ; 
 int /*<<< orphan*/  cf_chacha20_init (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  chacha20_dispose ; 
 int /*<<< orphan*/  chacha20_init ; 
 int /*<<< orphan*/  chacha20_transform ; 

__attribute__((used)) static int chacha20_setup_crypto(ptls_cipher_context_t *_ctx, int is_enc, const void *key)
{
    struct chacha20_context_t *ctx = (struct chacha20_context_t *)_ctx;
    ctx->super.do_dispose = chacha20_dispose;
    ctx->super.do_init = chacha20_init;
    ctx->super.do_transform = chacha20_transform;
    cf_chacha20_init(&ctx->chacha, key, PTLS_CHACHA20_KEY_SIZE, (const uint8_t *)"01234567" /* not used */);
    return 0;
}