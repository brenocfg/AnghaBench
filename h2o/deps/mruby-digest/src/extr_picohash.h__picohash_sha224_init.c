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
struct TYPE_3__ {int* state; scalar_t__ length; scalar_t__ curlen; } ;
typedef  TYPE_1__ _picohash_sha256_ctx_t ;

/* Variables and functions */

inline void _picohash_sha224_init(_picohash_sha256_ctx_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;
    ctx->state[0] = 0xc1059ed8UL;
    ctx->state[1] = 0x367cd507UL;
    ctx->state[2] = 0x3070dd17UL;
    ctx->state[3] = 0xf70e5939UL;
    ctx->state[4] = 0xffc00b31UL;
    ctx->state[5] = 0x68581511UL;
    ctx->state[6] = 0x64f98fa7UL;
    ctx->state[7] = 0xbefa4fa4UL;
}