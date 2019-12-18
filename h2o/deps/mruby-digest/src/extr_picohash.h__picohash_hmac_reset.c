#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* hash_reset ) (TYPE_2__*) ;} ;
struct TYPE_7__ {TYPE_1__ _hmac; } ;
typedef  TYPE_2__ picohash_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  _picohash_hmac_apply_key (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static inline void _picohash_hmac_reset(picohash_ctx_t *ctx)
{
    ctx->_hmac.hash_reset(ctx);
    _picohash_hmac_apply_key(ctx, 0x36);
}