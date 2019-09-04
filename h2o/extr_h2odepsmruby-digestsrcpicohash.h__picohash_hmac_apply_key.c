#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* key; } ;
struct TYPE_6__ {size_t block_length; TYPE_1__ _hmac; } ;
typedef  TYPE_2__ picohash_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  picohash_update (TYPE_2__*,unsigned char*,size_t) ; 

__attribute__((used)) static inline void _picohash_hmac_apply_key(picohash_ctx_t *ctx, unsigned char delta)
{
    size_t i;
    for (i = 0; i != ctx->block_length; ++i)
        ctx->_hmac.key[i] ^= delta;
    picohash_update(ctx, ctx->_hmac.key, ctx->block_length);
    for (i = 0; i != ctx->block_length; ++i)
        ctx->_hmac.key[i] ^= delta;
}